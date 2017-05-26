/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 12:02:35 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/25 17:29:52 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	FLAGS VALUES:
**		1:	LOW_DEF
**		2:	abs c
**		4:	break early (optimisation)
*/

static inline t_cmp	map(t_cmp *cmp, t_int2 *dims, t_env *env)
{
	cmp->re = (env->dimx.a + (env->dimx.b - env->dimx.a)
				* (double)(dims->a) / WIN_X);
	cmp->im = (env->dimy.a + (env->dimy.b - env->dimy.a)
				* (double)(dims->b) / WIN_Y);
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

int					draw_mandel(t_env *env, t_int2 *dims)
{
	t_cmp			c[2];
	t_doub2			tmp;
	int				iter;

	iter = 0;
	map(c, dims, env);
	c[1] = (env->params & 8) ? map(&env->mapped_mouse, &env->mouse, env) : c[0];
	while (iter < ((env->params & 1) ? LOW_ITER : MAX_ITER)
			&& (c->re * c->re + c->im * c->im) < MAX_MOD)
		do_iter(env->params, &tmp, c, &iter);
	if (iter == ((env->params & 1) ? LOW_ITER : MAX_ITER))
		return (0x0);
	else
	{
		do_iter((env->params & 0xB), &tmp, c, &iter);
		if ((env->params & 2))
			do_iter((env->params & 0xB), &tmp, c, &iter);
		return (color_smoothen(c, iter, env));
	}
	return (0);
}
