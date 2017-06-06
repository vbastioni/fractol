/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 10:44:08 by vbastion          #+#    #+#             */
/*   Updated: 2017/06/06 16:35:29 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void			env_setup_fract(t_env *e, const char *name)
{
	if (ft_strcmp(name, MANDEL) == 0)
		env_set_mandel(e, 0);
	else if (ft_strcmp(name, JULIA) == 0)
		env_set_mandel(e, 1);
	else if (ft_strcmp(name, SHIP) == 0)
		env_set_mandel(e, 2);
	else if (ft_strcmp(name, TREE) == 0)
		env_set_tree(e);
	else if (ft_strcmp(name, NEWTON) == 0)
		env_set_newton(e);
	else if (ft_strcmp(name, TRIANGLE) == 0)
		env_set_triangle(e);
	else if (ft_strcmp(name, SPONGE) == 0)
		env_set_sponge(e);
}

static void			env_setup_color(t_env *e)
{
	e->col_getter[0] = &color_get_gum;
	e->col_getter[1] = &color_get_bones;
	e->col_getter[2] = &color_get_blue;
	e->col_getter[3] = &color_get_copper;
	e->color_scale_id = 0;
}

static int			env_setup(t_env *e, const char *name)
{
	env_setup_fract(e, name);
	if ((img_create(e)) == 0)
		return (0 * err("Error with mlx image.\n"));
	e->mouse = (t_int2){0, 0};
	env_setup_color(e);
	e->zoom = 1.;
	e->z_iter = 0;
	e->delta = (t_doub2){ 0., 0. };
	return (1);
}

static void			env_defaults(t_env *e)
{
	e->img.img = NULL;
	e->win = NULL;
	e->zoom = 0;
	e->z_iter = 0;
	e->dimx = (t_doub2){ 0., 0. };
	e->dimy = (t_doub2){ 0., 0. };
	e->def_dimx = e->dimx;
	e->def_dimy = e->dimy;
}

int					main(int ac, char **av)
{
	t_env			e;

	env_defaults(&e);
	e.fnames = (char *[8]){MANDEL, JULIA, SHIP, TREE, NEWTON, TRIANGLE,
							SPONGE, 0};
	if (ac == 1 || (!valid_args(ac, av, &e)))
		return (usage(av[0], &e));
	if ((e.mlx = mlx_init()) == NULL)
		return (err("Could not init mlx.\n"));
	if ((e.win = mlx_new_window(e.mlx, WIN_X, WIN_Y, WIN_NAME)) == NULL)
		return (err("Could not create mlx window.\n") | cb_exit(&e));
	if ((env_setup(&e, av[1])) == 0)
		return (err("Could not setup e.\n") | cb_exit(&e));
	prep_threads(&e);
	mlx_key_hook(e.win, &handle_key, &e);
	mlx_hook(e.win, EVT_MOTION, EVT_MOTION_MASK, handle_mouse, &e);
	mlx_expose_hook(e.win, &expose, &e);
	mlx_mouse_hook(e.win, &handle_mouse_btn, &e);
	mlx_loop(e.mlx);
	return (0);
}
