/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 15:54:26 by vbastion          #+#    #+#             */
/*   Updated: 2017/06/21 16:00:16 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double				clamp_double(double val, double min, double max)
{
	if (val > max)
		val = max;
	if (val < min)
		val = min;
	return (val);
}

int					clamp(int val, int min, int max)
{
	if (val > max)
		val = max;
	if (val < min)
		val = min;
	return (val);
}

void				zoom(int x, int y, t_env *e, double z)
{
	double ox;
	double oy;
	double nx;
	double ny;
	double z2;

	z2 = (e->fid == 6 ? clamp_double(e->zoom * z, 0.5, 10)
			: clamp_double(e->zoom * z, 0., 10));
	ox = (e->dimx.b - e->dimx.a) * e->zoom;
	oy = (e->dimy.b - e->dimy.a) * e->zoom;
	nx = (e->dimx.b - e->dimx.a) * z2;
	ny = (e->dimy.b - e->dimy.a) * z2;
	e->z_iter = clamp(e->z_iter + ((z > 1) ? -2 : 2), 4, 1024);
	e->zoom = z2;
	e->delta.a -= ((double)x / WIN_X) * (nx - ox);
	e->delta.b -= ((double)y / WIN_Y) * (ny - oy);
	(e->fid < 4 ? rdr_cmd(e) : e->renderer(e));
}
