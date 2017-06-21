/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m3.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 17:48:25 by vbastion          #+#    #+#             */
/*   Updated: 2017/06/21 17:53:38 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	FLAGS VALUES:
**		1:	LOW_DEF
**		2:	abs c
**		4:	break early (optimisation)
*/

static inline t_cmp	map(t_cmp *cmp, t_int2 *dims, t_env *e)
{
	cmp->re = ((e->dimx.b - e->dimx.a) * ((double)dims->a / WIN_X)
				* e->zoom + e->delta.a + e->dimx.a);
	cmp->im = ((e->dimy.b - e->dimy.a) * ((double)dims->b / WIN_X)
				* e->zoom + e->delta.b + e->dimy.a);
	return (*cmp);
}

static int			do_iter(t_uchar flags, t_doub2 *tmp, t_cmp *c, int *iter)
{
	double			twoab;

	tmp->a = c->re * c->re * c->re;
	tmp->b = 3. * c->re * c->im * c->im;
	twoab = 3. * c->re * c->re * c->im - c->im * c->im * c->im;
	if ((flags & 4) && c->re == (tmp->a - tmp->b + (c + 1)->re)
		&& c->im == (twoab + (c + 1)->im))
		return (0);
	else
	{
		c->re = tmp->a - tmp->b + (c + 1)->re;
		c->im = twoab + (c + 1)->im;
	}
	(*iter)++;
	return (1);
}

int					draw_m3(t_env *e, t_int2 *dims)
{
	t_cmp			c[2];
	t_doub2			tmp;
	int				iter;

	iter = 0;
	map(c, dims, e);
	c[1] = (e->params & 8) ? map(&e->mapped_mouse, &e->mouse, e) : c[0];
	while (iter < (ITER + e->z_iter)
			&& (c->re * c->re + c->im * c->im) < MAX_MOD)
	{
		if (do_iter(e->params, &tmp, c, &iter) == 0)
			iter = (ITER + e->z_iter);
	}
	if (iter == (ITER + e->z_iter))
		return (0x0);
	else
	{
		do_iter((e->params & 0xB), &tmp, c, &iter);
		if ((e->params & 2))
			do_iter((e->params & 0xB), &tmp, c, &iter);
		return (color_smoothen(c, iter, e));
	}
}
