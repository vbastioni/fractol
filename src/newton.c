#include "fractol.h"

static inline t_cmp	map(t_cmp *cmp, t_int2 *dims, t_env *env)
{
	cmp->re = (env->dimx.a + (env->dimx.b - env->dimx.a)
				* (double)(dims->a) / WIN_X);
	cmp->im = (env->dimy.a + (env->dimy.b - env->dimy.a)
				* (double)(dims->b) / WIN_Y);
	return (*cmp);
}

static float	cmp_abs2(const t_cmp *lhs, const t_cmp *rhs)
{
	t_cmp	tmp;

	tmp.re = lhs->re - rhs->re;
	tmp.im = lhs->im - rhs->im;
	return (cmp_abs(&tmp));
}

int			draw_newton(t_env *env)
{
	int 		max_cnt = 255;
	int			mult_col = 15;
	float 		tol = .0001;
	const t_cmp	r[3] = (const t_cmp[3]){
		(const t_cmp){1., 0},
		(const t_cmp){-0.5, 0.86602540378},
		(const t_cmp){-0.5, -0.86602540378}
	};
	t_int2		dims = (t_int2){0, 0};
	int			cnt;
	double		max_mod;
	t_color		col;

	img_clear(env);
	while (dims.b < WIN_Y)
	{
		dims.a = 0;
		while (dims.a < WIN_X)
		{
			t_cmp curr;
			map(&curr, &dims, env);
			cnt = 0;
			max_mod = 0.;
			while ((cnt < max_cnt) && cmp_abs2(&curr, r) > tol
					&& cmp_abs2(&curr, (r + 1)) > tol && cmp_abs2(&curr, (r + 2)) > tol)
			{
				if (cmp_abs(&curr) > 0)
				{
					t_cmp ta;
					t_cmp tb;
					t_cmp tc;
					tc = cmp_mult(&curr, &curr);
					tb = cmp_mult(&tc, &curr);
					ta = (t_cmp){1., 0.};
					ta = cmp_sub(&tb, &ta);
					tb = cmp_multr(&tc, 3.0);
					tc = cmp_div(&ta, &tb);
					curr = cmp_sub(&curr, &tc);
				}
				if (env->newton_mode && cmp_abs(&curr) > max_mod)
					max_mod = cmp_abs(&curr);
				cnt++;
			}
			col.co = 0x0;
			if (cmp_abs2(&curr, r) < tol)
				col.c[2] = 255 - (env->newton_mode ? max_mod : cnt) * mult_col;
			if (cmp_abs2(&curr, (r + 1)) <= tol)
				col.c[1] = 255 - (env->newton_mode ? max_mod : cnt) * mult_col;
			if (cmp_abs2(&curr, (r + 2)) <= tol)
				col.c[0] = 255 - (env->newton_mode ? max_mod : cnt) * mult_col;
			*(img_get_addr(env, &dims)) = col.co;
			dims.a++;
		}
		dims.b++;
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}
