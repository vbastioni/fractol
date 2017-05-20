/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 10:22:59 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/20 10:23:02 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int					color_get(double val)
{
	const double	*scales[3] = (const double *[3]) {
		(const double[2]){0., 1.},
		(const double[2]){0., 1.},
		(const double[2]){1., 1.}
	};
	t_color			c;
	double			de;

	de = val / MAX_ITER;
	c.c[3] = 0x0;
	c.c[2] = (scales[0][0] + (scales[0][1] - scales[0][0]) * de) * 0xFF * 100;
	c.c[1] = (scales[1][0] + (scales[1][1] - scales[1][0]) * de) * 0xFF * 100;
	c.c[0] = (scales[2][0] + (scales[2][1] - scales[2][0]) * de) * 0xFF * 100;
	return (c.co);
}

int					color_smoothen(t_cmp *c, long index)
{
	double			zn;
	double			nu;
	double			i;

	zn = log(c->re * c->re + c->im * c->im) / 2.;
	nu = log(zn / log(2.)) / log(2.);
	i = index + 1 - nu;
	if (i < 0)
		i = 0;
	return (color_get(i));
}
