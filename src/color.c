/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 10:22:59 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/25 13:53:14 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
		col.co = 0xFFFFFF;
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

int					color_get(double val, t_env *env)
{
	const double	*scales[3] = (const double *[3]) {
		(const double[2]){0., 1.},
			(const double[2]){0., 1.},
			(const double[2]){1., 1.}
	};
	t_color			c;
	double			de;

	(void)env;
	de = val / MAX_ITER;
	c.c[3] = 0x0;
	c.c[2] = (scales[0][0] + (scales[0][1] - scales[0][0]) * de) * 0xFF * 100;
	c.c[1] = (scales[1][0] + (scales[1][1] - scales[1][0]) * de) * 0xFF * 100;
	c.c[0] = (scales[2][0] + (scales[2][1] - scales[2][0]) * de) * 0xFF * 100;
	return (c.co);
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
	(void)env;
	return (color_get(i, env));
}
