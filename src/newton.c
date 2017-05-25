/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 11:09:37 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/25 17:32:26 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline t_cmp	map(t_cmp *cmp, t_int2 *dims, t_env *env)
{
	cmp->re = (env->dimx.a + (env->dimx.b - env->dimx.a)
			* (double)(dims->a) / WIN_X);
	cmp->im = (env->dimy.a + (env->dimy.b - env->dimy.a)
			* (double)(dims->b) / WIN_Y);
	return (*cmp);
}

static float		cmp_abs2(const t_cmp *lhs, const t_cmp *rhs)
{
	t_cmp			tmp;

	tmp.re = lhs->re - rhs->re;
	tmp.im = lhs->im - rhs->im;
	return (cmp_abs(&tmp));
}

static inline void	cmp_cvt(t_cmp *curr)
{
	t_cmp			ta;
	t_cmp			tb;
	t_cmp			tc;

	if (cmp_abs(curr) > 0)
	{
		tc = cmp_mult(curr, curr);
		tb = cmp_mult(&tc, curr);
		ta = (t_cmp){1., 0.};
		ta = cmp_sub(&tb, &ta);
		tb = cmp_multr(&tc, 3.0);
		tc = cmp_div(&ta, &tb);
		*curr = cmp_sub(curr, &tc);
	}
}

static inline int	get_color(const t_cmp *curr, const t_env *env,
								const double *max_mod, const int cnt)
{
	t_color			col;
	int				m;
	int				n;

	m = env->newton_mode;
	n = ((env->newton_mode & 1) == 1) ? *max_mod : cnt;
	col.co = ((m < 2) ? color_scale_get(n / (double)N_MAX_CNT, env) : 0);
	if (cmp_abs2(curr, env->r) < N_TOL)
		col.c[2] = ((m < 2) ? col.c[2] : n) * N_MULT_COL;
	if (cmp_abs2(curr, (env->r + 1)) <= N_TOL)
		col.c[1] = ((m < 2) ? col.c[1] : n) * N_MULT_COL;
	if (cmp_abs2(curr, (env->r + 2)) <= N_TOL)
		col.c[0] = ((m < 2) ? col.c[0] : n) * N_MULT_COL;
	return (col.co);
}

int					draw_newton(t_env *env, t_int2 *pos)
{
	t_cmp			curr;
	int				cnt;
	double			max_mod;

	map(&curr, pos, env);
	cnt = 0;
	max_mod = 0.;
	while ((cnt < N_MAX_CNT) && cmp_abs2(&curr, env->r) > N_TOL
			&& cmp_abs2(&curr, (env->r + 1)) > N_TOL
			&& cmp_abs2(&curr, (env->r + 2)) > N_TOL)
	{
		cmp_cvt(&curr);
		if (env->newton_mode && cmp_abs(&curr) > max_mod)
			max_mod = cmp_abs(&curr);
		cnt++;
	}
	return (get_color(&curr, env, &max_mod, cnt));
}
