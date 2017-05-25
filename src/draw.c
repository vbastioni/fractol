/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 12:02:35 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/25 12:21:57 by vbastion         ###   ########.fr       */
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

static void			do_iter(t_uchar flags, t_doub2 *tmp, t_cmp *curr, t_cmp *c,
							int *iter)
{
	double			twoab;

	tmp->a = curr->re * curr->re;
	tmp->b = curr->im * curr->im;
	if ((flags & 4) && curr->re == (tmp->a - tmp->b + c->re)
		&& curr->im == (2 * tmp->a * tmp->b + c->im))
		*iter = ((flags & 1) ? LOW_ITER : MAX_ITER) - 1;
	else
	{
		twoab = 2 * ((flags & 2) ? fabs(curr->re) * fabs(curr->im) :
						curr->re * curr->im);
		curr->re = tmp->a - tmp->b + c->re;
		curr->im = twoab + c->im;
	}
	(*iter)++;
}

 int				draw_mandel(t_env *env, t_int2 *dims)
{
	t_cmp			curr;
	t_cmp			c;
	t_doub2			tmp;
	int				iter;

	iter = 0;
	map(&curr, dims, env);
	c = (env->params & 8) ? map(&env->mapped_mouse, &env->mouse, env) : curr;
	while (iter < ((env->params & 1) ? LOW_ITER : MAX_ITER)
			&& (curr.re * curr.re + curr.im * curr.im) < MAX_MOD)
		do_iter(env->params, &tmp, &curr, &c, &iter);
	if (iter == ((env->params & 1) ? LOW_ITER : MAX_ITER))
		return (0x0);
	else
	{
		do_iter((env->params & 0xB), &tmp, &curr, &c, &iter);
		if ((env->params & 2))
			do_iter((env->params & 0xB), &tmp, &curr, &c, &iter);
		return (color_smoothen(&curr, iter, env));
	}
	return (0);
}
