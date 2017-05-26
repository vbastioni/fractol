/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 10:22:59 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/25 17:15:46 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int					color_get_copper(double val)
{
	const double	a = .809524;
	t_color			col;

	col.co = 0x0;
	col.c[0] = .4975 * val * 255 * 100;
	col.c[1] = .7812 * val * 255 * 100;
	col.c[2] = ((val < a) ? val / a : 1) * 255;
	return (col.co);
}

int					color_get_bones(double val)
{
	const double	a = .365079;
	const double	b = .746032;
	t_color			col;

	col.co = 0x0;
	if (val < a)
	{
		col.c[2] = .319444 * (val / a) * 255 * 100;
		col.c[1] = .319444 * (val / a) * 255 * 100;
		col.c[0] = .444444 * (val / a) * 255 * 100;
	}
	else if (val < b)
	{
		col.c[2] = (.652778 - .319444) * ((val - a) / (b - a)) * 255 * 100;
		col.c[1] = (.777778 - .319444) * ((val - a) / (b - a)) * 255 * 100;
		col.c[0] = (.777778 - .444444) * ((val - a) / (b - a)) * 255 * 100;
	}
	else
	{
		col.c[2] = (1. - .652778) * ((val - b) / (1. - b)) * 255 * 100;
		col.c[1] = (1. - .777778) * ((val - b) / (1. - b)) * 255 * 100;
		col.c[0] = (1. - .777778) * ((val - b) / (1. - b)) * 255 * 100;
	}
	return (col.co);
}

int					color_get_blue(double val)
{
	t_color			col;

	col.co = 0x0;
	col.c[2] = 0xFF * val * 100;
	col.c[1] = 0xFF * val * 100;
	col.c[0] = 0xFF;
	return (col.co);
}

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
	return (color_scale_get(i / MAX_ITER, env));
}
