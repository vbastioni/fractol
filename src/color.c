/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 10:22:59 by vbastion          #+#    #+#             */
/*   Updated: 2017/06/05 13:59:07 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int					color_scale_get(double progress, const t_env *env)
{
	return (env->col_getter[env->color_scale_id](progress));
}

int					color_smoothen(t_cmp *c, long index, t_env *env)
{
	double			zn;
	double			nu;
	double			i;

	zn = log(c->re * c->re + c->im * c->im) / 2.;
	nu = log(zn / log(2.)) / log(2.);
	i = index + 1 - nu;
	if (i < 0)
		i = 0;
	return (color_scale_get(i / ITER, env));
}
