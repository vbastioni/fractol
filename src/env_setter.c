/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 16:17:44 by vbastion          #+#    #+#             */
/*   Updated: 2017/06/05 15:54:44 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				env_set_mandel(t_env *e, int id)
{
	if (id == 0)
	{
		e->dimx = (t_doub2){-2., 1.};
		e->dimy = (t_doub2){-1.5, 1.5};
	}
	else if (id == 1)
	{
		e->dimx = (t_doub2){-2., 2.};
		e->dimy = (t_doub2){-2., 2.};
	}
	else if (id == 2)
	{
		e->dimx = (t_doub2){-2., 1.5};
		e->dimy = (t_doub2){-2., 1.5};
	}
	e->def_dimx = e->dimx;
	e->def_dimy = e->dimy;
	e->renderer = &draw_mandel;
	e->fid = 1;
	e->params = ((id == 1) << 0) | ((id == 2) << 1) | 1 << 2 | ((id == 1) << 3);
}

void				env_set_tree(t_env *e)
{
	e->dimx = (t_doub2){-(WIN_X / 2.), WIN_X / 2.};
	e->dimy = (t_doub2){-(WIN_Y / 2.), WIN_Y / 2.};
	e->def_dimx = e->dimx;
	e->def_dimy = e->dimy;
	e->renderer = &draw_tree;
	e->tree_min_len = 1.;
	e->tree_step = .67;
	e->tree_len = 50;
	e->fid = 4;
}

void				env_set_newton(t_env *e)
{
	e->dimx = (t_doub2){-(WIN_X / 2.), WIN_X / 2.};
	e->dimy = (t_doub2){-(WIN_Y / 2.), WIN_Y / 2.};
	e->def_dimx = e->dimx;
	e->def_dimy = e->dimy;
	e->r[0] = (t_cmp){1., 0.};
	e->r[1] = (t_cmp){-.5, .86602540378};
	e->r[2] = (t_cmp){-.5, -.86602540378};
	e->dimx = (t_doub2){-2., 2.};
	e->dimy = (t_doub2){-2., 2.};
	e->def_dimx = e->dimx;
	e->def_dimy = e->dimy;
	e->renderer = &draw_newton;
	e->newton_mode = 0;
	e->fid = 3;
}

void				env_set_sponge(t_env *e)
{
	e->dimx = (t_doub2){-(WIN_X / 2.), WIN_X / 2.};
	e->dimy = (t_doub2){-(WIN_Y / 2.), WIN_Y / 2.};
	e->def_dimx = e->dimx;
	e->def_dimy = e->dimy;
	e->renderer = &draw_sponge;
	e->sponge_depth = 4;
	e->fid = 5;
}

void				env_set_triangle(t_env *e)
{
	e->dimx = (t_doub2){-(WIN_X / 2.), WIN_X / 2.};
	e->dimy = (t_doub2){-(WIN_Y / 2.), WIN_Y / 2.};
	e->def_dimx = e->dimx;
	e->def_dimy = e->dimy;
	e->renderer = &draw_triangle;
	e->tri_depth = 4;
	e->fid = 6;
}
