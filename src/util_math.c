/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 15:54:26 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/26 15:54:47 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int					clamp(int val, int min, int max)
{
	if (val > max)
		val = max;
	if (val < min)
		val = min;
	return (val);
}

#include <stdio.h>

void				zoom(int x, int y, t_env *e, double z)
{
	double ox;
	double oy;
	double nx;
	double ny;

	ox = (e->dimx.b - e->dimx.a) * e->zoom;
	oy = (e->dimy.b - e->dimy.a) * e->zoom;
	nx = (e->dimx.b - e->dimx.a) * e->zoom * z;
	ny = (e->dimy.b - e->dimy.a) * e->zoom * z;
	e->z_iter = clamp(e->z_iter + ((z > 1) ? -4 : 4), 4, 2048);
	e->zoom *= z;
	e->delta.a -= ((double)x / WIN_X) * (nx - ox);
	e->delta.b -= ((double)y / WIN_Y) * (ny - oy);
	rdr_cmd(e);
}
