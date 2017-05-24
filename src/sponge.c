#include "fractol.h"

static void	draw_line(t_env *env, t_int2 *from, t_int2 *to)
{
	t_int2	curr;
	t_int2	delta;
	double	len;
	int		i;

	i = 0;
	delta = (t_int2){ to->a - from->a, to->b - from->b };
	len = sqrt(delta.a * delta.a + delta.b * delta.b);
	if (len == 0)
		return ;
	while (i < len)
	{
		curr.a = from->a + (int)(delta.a * i / len);
		curr.b = from->b + (int)(delta.b * i / len);
		if (!(curr.a >= WIN_X || curr.a < 0 || curr.b >= WIN_Y || curr.b < 0))
			*(img_get_addr(env, &curr)) = 0xFFFFFF;
		i++;
	}
}

static void	draw_cube(t_env *env, int level, int x, int y, double r)
{
	t_int2		pos[4];
	double		delta;

	if (level >= env->sponge_depth)
		return ;
	delta = r / 3;
	pos[0] = (t_int2){ x - delta, y - delta };
	pos[1] = (t_int2){ x + delta, y - delta };
	pos[2] = (t_int2){ x + delta, y + delta };
	pos[3] = (t_int2){ x - delta, y + delta };
	draw_line(env, pos, pos + 1);
	draw_line(env, pos + 1, pos + 2);
	draw_line(env, pos + 2, pos + 3);
	draw_line(env, pos + 3, pos);
	draw_cube(env, ++level, x - delta * 2, y + delta * 2, r / 3);
	draw_cube(env, level, x, y + delta * 2, delta);
	draw_cube(env, level, x + delta * 2, y + delta * 2, delta);
	draw_cube(env, level, x + delta * 2, y, delta);
	draw_cube(env, level, x + delta * 2, y - delta * 2, delta);
	draw_cube(env, level, x, y - delta * 2, delta);
	draw_cube(env, level, x - delta * 2, y - delta * 2, delta);
	draw_cube(env, level, x - delta * 2, y, delta);
}

int			draw_sponge(t_env *env)
{
	img_clear(env);
	env->sponge_depth = 6;
	draw_cube(env, 0, WIN_X / 2, WIN_Y / 2, 600.);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}
