/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 12:02:35 by vbastion          #+#    #+#             */
/*   Updated: 2017/06/05 11:58:14 by vbastion         ###   ########.fr       */
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

static void			do_iter(t_uchar flags, t_doub2 *tmp, t_cmp *c, int *iter)
{
	double			twoab;

	tmp->a = c->re * c->re;
	tmp->b = c->im * c->im;
	if ((flags & 4) && c->re == (tmp->a - tmp->b + (c + 1)->re)
		&& c->im == (2 * tmp->a * tmp->b + (c + 1)->im))
		*iter = ((flags & 1) ? LOW_ITER : MAX_ITER) - 1;
	else
	{
		twoab = 2 * ((flags & 2) ? fabs(c->re) * fabs(c->im) :
						c->re * c->im);
		c->re = tmp->a - tmp->b + (c + 1)->re;
		c->im = twoab + (c + 1)->im;
	}
	(*iter)++;
}

int					draw_mandel(t_env *e, t_int2 *dims)
{
	t_cmp			c[2];
	t_doub2			tmp;
	int				iter;

	iter = 0;
	map(c, dims, e);
	c[1] = (e->params & 8) ? map(&e->mapped_mouse, &e->mouse, e) : c[0];
	while (iter < (((e->params & 1) ? LOW_ITER : MAX_ITER) + e->z_iter)
			&& (c->re * c->re + c->im * c->im) < MAX_MOD)
		do_iter(e->params, &tmp, c, &iter);
	if (iter == ((e->params & 1) ? LOW_ITER : MAX_ITER))
		return (0x0);
	else
	{
		do_iter((e->params & 0xB), &tmp, c, &iter);
		if ((e->params & 2))
			do_iter((e->params & 0xB), &tmp, c, &iter);
		return (color_smoothen(c, iter, e));
	}
	return (0);
}
