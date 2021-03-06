/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 11:09:37 by vbastion          #+#    #+#             */
/*   Updated: 2017/06/05 11:58:51 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline t_cmp	map(t_cmp *cmp, t_int2 *dims, t_env *e)
{
	((e->zoom > 200) ? (e->zoom = 200) : 0);
	cmp->re = ((e->dimx.b - e->dimx.a) * ((double)dims->a / WIN_X)
				* e->zoom + e->delta.a + e->dimx.a);
	cmp->im = ((e->dimy.b - e->dimy.a) * ((double)dims->b / WIN_Y)
				* e->zoom + e->delta.b + e->dimy.a);
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

static inline int	get_color(const t_cmp *curr, const t_env *e,
		const double *max_mod, const int cnt)
{
	t_color			col;
	int				m;
	int				n;
	t_uchar			flag;

	flag = ((cmp_abs2(curr, e->r) < N_TOL)
			| ((cmp_abs2(curr, e->r + 1) <= N_TOL) << 1)
			| ((cmp_abs2(curr, e->r + 2) <= N_TOL) << 2));
	m = e->newton_mode;
	n = ((e->newton_mode & 1) == 1) ? *max_mod : cnt;
	col.co = ((m < 2) ? color_scale_get(n / (double)N_MAX_CNT, e) : n);
	if (m < 4)
	{
		if (flag & 1)
			col.c[2] = ((m < 2) ? col.c[2] : n) * N_MULT_COL;
		if (flag & 2)
			col.c[1] = ((m < 2) ? col.c[1] : n) * N_MULT_COL;
		if (flag & 4)
			col.c[0] = ((m < 2) ? col.c[0] : n) * N_MULT_COL;
	}
	else if (flag != 0)
		col.co = color_scale_get(n / (double)N_MAX_CNT * N_MULT_COL, e);
	return (col.co);
}

int					draw_newton(t_env *e, t_int2 *pos)
{
	t_cmp			curr;
	int				cnt;
	double			max_mod;
	int				max;

	max = clamp(N_MAX_CNT + e->z_iter, 4, 256);
	map(&curr, pos, e);
	cnt = 0;
	max_mod = 0.;
	while ((cnt < max) && cmp_abs2(&curr, e->r) > N_TOL
			&& cmp_abs2(&curr, (e->r + 1)) > N_TOL
			&& cmp_abs2(&curr, (e->r + 2)) > N_TOL)
	{
		cmp_cvt(&curr);
		if (e->newton_mode && cmp_abs(&curr) > max_mod)
			max_mod = cmp_abs(&curr);
		cnt++;
	}
	return (get_color(&curr, e, &max_mod, cnt));
}
