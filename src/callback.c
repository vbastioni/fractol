/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 12:31:30 by vbastion          #+#    #+#             */
/*   Updated: 2017/06/06 16:31:22 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				reset(t_env *e)
{
	e->dimx = e->def_dimx;
	e->dimy = e->def_dimy;
	e->zoom = 1.;
	e->z_iter = 0;
	e->delta = (t_doub2){ 0., 0. };
	(e->fid > 3) ? e->renderer(e) : rdr_cmd(e);
	return (0);
}

int				change_mode(t_env *e)
{
	if (e->fid != 3)
		return (0);
	e->newton_mode++;
	if (e->newton_mode > 5)
		e->newton_mode = 0;
	(e->fid > 3) ? e->renderer(e) : rdr_cmd(e);
	return (1);
}

int				swap_color(t_env *e)
{
	e->color_scale_id++;
	if (e->color_scale_id == COL_GRAD_CNT)
		e->color_scale_id = 0;
	(e->fid > 3) ? e->renderer(e) : rdr_cmd(e);
	return (0);
}

int				expose(void *param)
{
	t_env		*e;

	e = (t_env *)param;
	(e->fid > 3) ? e->renderer(e) : rdr_cmd(e);
	return (0);
}

int				cb_exit(t_env *e)
{
	if (e->img.img != NULL)
		mlx_destroy_image(e->mlx, e->img.img);
	if (e->win != NULL)
		mlx_destroy_window(e->mlx, e->win);
	exit(0);
	return (0);
}
