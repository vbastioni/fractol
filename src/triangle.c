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

static int	draw_tri(t_env *env,t_int2 *pos, int len, int depth)
{
	t_int2 lp;
	t_int2 hp;
	int		half;

	if (depth == 0)
		return (0);
	half = len / 2;
	lp = (t_int2){ pos->a - len, pos->b };
	hp = (t_int2){ pos->a - half, pos->b - sqrt(half * half + len * len) };
	draw_line(env, pos, &lp);
	draw_line(env, pos, &hp);
	draw_line(env, &hp, &lp);
	depth--;
	lp = (t_int2){ pos->a - half, pos->b };
	draw_tri(env, &lp, half, depth);
	lp = (t_int2){ pos->a - len / 4, 
					pos->b - sqrt(half * half + len * len) / 2 };
	draw_tri(env, &lp, half, depth);
	lp = (t_int2){ pos->a, pos->b };
	draw_tri(env, &lp, half, depth);
	return (0);
}

int		draw_triangle(t_env *env)
{
	t_int2 init;

	init = (t_int2){WIN_X - 1, WIN_Y - 1};
	img_clear(env);
	draw_tri(env, &init, WIN_X - 100, 7);
	img_to_win(env);
	return (0);
}
