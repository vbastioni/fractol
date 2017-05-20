/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 10:44:08 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/20 14:15:01 by vbastion         ###   ########.fr       */
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
	env->params = to_param(1, 0, 1, 1);
}

void				env_set_mandel(t_env *env)
{
	env->dimx = (t_doub2){-2., 1.};
	env->dimy = (t_doub2){-1.5, 1.5};
	env->params = to_param(0, 0, 1, 0);
}

void				env_set_ship(t_env *env)
{
	env->dimx = (t_doub2){-2., 1.5};
	env->dimy = (t_doub2){-2., 1.5};
	env->params = to_param(0, 1, 1, 0);
}

int					env_setup(t_env *env, const char *name)
{
	if (ft_strcmp(name, JULIA) == 0)
		env_set_julia(env);
	else if (ft_strcmp(name, MANDEL) == 0)
		env_set_mandel(env);
	else if (ft_strcmp(name, SHIP) == 0)
		env_set_ship(env);
	if (!(img_create(env)))
		return (0 * err("Error with mlx image.\n"));
	env->mouse = (t_int2){0, 0};
	env->renderer = &draw;
	return (0);
}

int					main(int ac, char **av)
{
	t_env			env;

	env.fnames = (char *[4]){MANDEL, JULIA, SHIP, 0};
	if (ac == 1 || (!valid_args(ac, av, &env))) 
		return (usage(av[0], &env));
	if (!(env.mlx = mlx_init()))
		return (err("Could not init mlx.\n"));
	if (!(env.win = mlx_new_window(env.mlx, WIN_X, WIN_Y, WIN_NAME)))
		return (err("Could not create mlx window.\n"));
	env_setup(&env, av[1]);
	env.renderer(&env);
	mlx_key_hook(env.win, &handle_key, &env);
	mlx_hook(env.win, EVT_MOTION, EVT_MOTION_MASK, handle_mouse, &env);
	mlx_expose_hook(env.win, &expose, &env);
	mlx_loop(env.mlx);
	return (0);
}
