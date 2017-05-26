/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 10:44:08 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/26 14:22:15 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_uchar		to_param(t_uchar low_def, t_uchar abs, t_uchar opti,
								t_uchar mouse)
{
	return ((low_def << 0) | (abs << 1) | (opti << 2) | (mouse << 3));
}

void				env_set_julia(t_env *e)
{
	e->dimx = (t_doub2){-2., 2.};
	e->dimy = (t_doub2){-2., 2.};
	e->def_dimx = e->dimx;
	e->def_dimy = e->dimy;
	e->params = to_param(1, 0, 1, 1);
	e->renderer = &draw_mandel;
	e->fid = 1;
}

void				env_set_mandel(t_env *e)
{
	e->dimx = (t_doub2){-2., 1.};
	e->dimy = (t_doub2){-1.5, 1.5};
	e->def_dimx = e->dimx;
	e->def_dimy = e->dimy;
	e->params = to_param(0, 0, 1, 0);
	e->renderer = &draw_mandel;
	e->fid = 0;
}

void				env_set_ship(t_env *e)
{
	e->dimx = (t_doub2){-2., 1.5};
	e->dimy = (t_doub2){-2., 1.5};
	e->def_dimx = e->dimx;
	e->def_dimy = e->dimy;
	e->params = to_param(0, 1, 1, 0);
	e->renderer = &draw_mandel;
	e->fid = 2;
}

void				env_set_tree(t_env *e)
{
	e->renderer = &draw_tree;
	e->tree_min_len = 1.;
	e->tree_step = .67;
	e->tree_len = 50;
	e->fid = 4;
}

void				env_set_newton(t_env *e)
{
	e->r[0] = (t_cmp){1., 0.};
	e->r[1] = (t_cmp){-.5, .86602540378};
	e->r[2] = (t_cmp){-.5, -.86602540378};
	e->dimx = (t_doub2){-2., 2.};
	e->dimy = (t_doub2){-2., 2.};
	e->renderer = &draw_newton;
	e->newton_mode = 0;
	e->fid = 3;
}

void				env_set_sponge(t_env *e)
{
	e->renderer = &draw_sponge;
	e->sponge_depth = 4;
	e->fid = 5;
}

void				env_set_triangle(t_env *e)
{
	e->renderer = &draw_triangle;
	e->fid = 6;
}

int					env_setup(t_env *e, const char *name)
{
	if (ft_strcmp(name, JULIA) == 0)
		env_set_julia(e);
	else if (ft_strcmp(name, MANDEL) == 0)
		env_set_mandel(e);
	else if (ft_strcmp(name, SHIP) == 0)
		env_set_ship(e);
	else if (ft_strcmp(name, TREE) == 0)
		env_set_tree(e);
	else if (ft_strcmp(name, NEWTON) == 0)
		env_set_newton(e);
	else if (ft_strcmp(name, TRIANGLE) == 0)
		env_set_triangle(e);
	else if (ft_strcmp(name, SPONGE) == 0)
		env_set_sponge(e);
	if (!(img_create(e)))
		return (0 * err("Error with mlx image.\n"));
	e->mouse = (t_int2){0, 0};
	if (!(e->pixels = (int *)malloc(sizeof(int) * (WIN_X * WIN_Y))))
		return (0 * err("Could not allocate pixel array.\n"));
	e->col_getter[0] = &color_get_bones;
	e->col_getter[1] = &color_get_blue;
	e->col_getter[2] = &color_get_copper;
	e->col_getter[3] = &color_get_gum;
	e->color_scale_id = 0;
	return (1);
}

int					main(int ac, char **av)
{
	t_env			e;

	e.fnames = (char *[8]){MANDEL, JULIA, SHIP, TREE, NEWTON, TRIANGLE,
							SPONGE, 0};
	if (ac == 1 || (!valid_args(ac, av, &e)))
		return (usage(av[0], &e));
	if (!(e.mlx = mlx_init()))
		return (err("Could not init mlx.\n"));
	if (!(e.win = mlx_new_window(e.mlx, WIN_X, WIN_Y, WIN_NAME)))
		return (err("Could not create mlx window.\n"));
	if (!(env_setup(&e, av[1])))
		return (err("Could not setup e.\n"));
	mlx_key_hook(e.win, &handle_key, &e);
	mlx_hook(e.win, EVT_MOTION, EVT_MOTION_MASK, handle_mouse, &e);
	mlx_expose_hook(e.win, &expose, &e);
	mlx_mouse_hook(e.win, &handle_mouse_btn, &e);
	mlx_loop(e.mlx);
	return (0);
}
