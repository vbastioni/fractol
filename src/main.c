/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 10:44:08 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/25 11:23:23 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_uchar		to_param(t_uchar low_def, t_uchar abs, t_uchar opti,
								t_uchar mouse)
{
	return ((low_def << 0) | (abs << 1) | (opti << 2) | (mouse << 3));
}

void				env_set_julia(t_env *env)
{
	env->dimx = (t_doub2){-2., 2.};
	env->dimy = (t_doub2){-2., 2.};
	env->def_dimx = env->dimx;
	env->def_dimy = env->dimy;
	env->params = to_param(1, 0, 1, 1);
	env->renderer = &draw_mandel;
}

void				env_set_mandel(t_env *env)
{
	env->dimx = (t_doub2){-2., 1.};
	env->dimy = (t_doub2){-1.5, 1.5};
	env->def_dimx = env->dimx;
	env->def_dimy = env->dimy;
	env->params = to_param(0, 0, 1, 0);
	env->renderer = &draw_mandel;
}

void				env_set_ship(t_env *env)
{
	env->dimx = (t_doub2){-2., 1.5};
	env->dimy = (t_doub2){-2., 1.5};
	env->def_dimx = env->dimx;
	env->def_dimy = env->dimy;
	env->params = to_param(0, 1, 1, 0);
	env->renderer = &draw_mandel;
}

void				env_set_tree(t_env *env)
{
	env->renderer = &draw_tree;
	env->tree_min_len = 1.;
	env->tree_step = .67;
}

void				env_set_newton(t_env *env)
{
	env->r[0] = (t_cmp){1., 0.};
	env->r[1] = (t_cmp){-.5, .86602540378};
	env->r[2] = (t_cmp){-.5, -.86602540378};
	env->dimx = (t_doub2){-2., 2.};
	env->dimy = (t_doub2){-2., 2.};
	env->renderer = &draw_newton;
	env->newton_mode = 1;
}

void				env_set_sponge(t_env *env)
{
	env->renderer = &draw_sponge;
}

void				env_set_triangle(t_env *env)
{
	env->renderer = &draw_triangle;
}

int					env_setup(t_env *env, const char *name)
{
	if (ft_strcmp(name, JULIA) == 0)
		env_set_julia(env);
	else if (ft_strcmp(name, MANDEL) == 0)
		env_set_mandel(env);
	else if (ft_strcmp(name, SHIP) == 0)
		env_set_ship(env);
	else if (ft_strcmp(name, TREE) == 0)
		env_set_tree(env);
	else if (ft_strcmp(name, NEWTON) == 0)
		env_set_newton(env);
	else if (ft_strcmp(name, TRIANGLE) == 0)
		env_set_triangle(env);
	else if (ft_strcmp(name, SPONGE) == 0)
		env_set_sponge(env);
	if (!(img_create(env)))
		return (0 * err("Error with mlx image.\n"));
	env->mouse = (t_int2){0, 0};
	if (!(env->pixels = (int *)malloc(sizeof(int) * (WIN_X * WIN_Y))))
		return (0 * err("Could not allocate pixel array.\n"));
	return (1);
}

int					main(int ac, char **av)
{
	t_env			env;

	env.fnames = (char *[8]){MANDEL, JULIA, SHIP, TREE, NEWTON, TRIANGLE,
								SPONGE, 0};
	if (ac == 1 || (!valid_args(ac, av, &env))) 
		return (usage(av[0], &env));
	if (!(env.mlx = mlx_init()))
		return (err("Could not init mlx.\n"));
	if (!(env.win = mlx_new_window(env.mlx, WIN_X, WIN_Y, WIN_NAME)))
		return (err("Could not create mlx window.\n"));
	if (!(env_setup(&env, av[1])))
		return (err("Could not setup env.\n"));
	mlx_key_hook(env.win, &handle_key, &env);
	mlx_hook(env.win, EVT_MOTION, EVT_MOTION_MASK, handle_mouse, &env);
	mlx_expose_hook(env.win, &expose, &env);
	mlx_mouse_hook(env.win, &handle_mouse_btn, &env);
	mlx_loop(env.mlx);
	return (0);
}
