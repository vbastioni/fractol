/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 10:44:08 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/18 16:19:46 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include "libft.h"

int				usage(char *name, t_env *env)
{
	char		**fnames;

	fnames = env->fnames;
	ft_putstr("\e[31mUsage:\e[0m ");
	ft_putstr(name);
	ft_putstr("\e[32m <fractal> \e[33m[<fractal>]\e[0m\n");
	while (*fnames)
	{
		ft_putstr("\t");
		ft_putstr(*fnames);
		ft_putstr("\n");
		fnames++;
	}
	return (0);
}

int				valid_args(int ac, char **av, t_env *env)
{
	char		**fnames;
	t_uchar		flags;

	flags = 0;
	fnames = env->fnames;
	while (*fnames)
	{
		if ((flags & 1) == 0 && ft_strcmp(*fnames, av[1]) == 0)
			flags |= 1;
		if (ac == 3 && (flags & 2) == 0 && ft_strcmp(*fnames, av[2]) == 0)
			flags |= 2;
		fnames++;
	}
	if (ac == 3 && (flags & 2) == 0)
		return (0);
	return (flags);
}

#ifdef DEBUG

int				err(const char *msg)
{
	ft_putstr(msg);
	return (1);
}

#else

int				err(const char *msg)
{
	(void)msg;
	return (1);
}

int				move(int kc, t_env *env)
{
	t_doub2		delta;

	delta.a = (env->dimx.b - env->dimx.a) * .1;
	delta.b = (env->dimy.b - env->dimy.a) * .1;

	if (kc == KC_D)
	{
		env->dimx.a += delta.a;
		env->dimx.b += delta.a;
	}
	else if (kc == KC_A)
	{
		env->dimx.a -= delta.a;
		env->dimx.b -= delta.a;
	}
	else if (kc == KC_S)
	{
		env->dimy.a += delta.a;
		env->dimy.b += delta.a;
	}
	else if (kc == KC_W)
	{
		env->dimy.a -= delta.a;
		env->dimy.b -= delta.a;
	}
	draw(env);
	return (1);
}

#endif

int				hk(int kc, void *param)
{
	t_env		*env;

	env = (t_env *)param;
	if (kc == KC_EXIT)
		exit(0);
	if (kc == KC_LEFT || kc == KC_A || kc == KC_RIGHT || kc == KC_D
		|| kc == KC_DOWN || kc == KC_S || kc == KC_UP || kc == KC_W)
		move(kc, env);
	return (0);
}

int				main(int ac, char **av)
{
	t_env		env;

	env.fnames = (char *[4]){MANDEL, JULIA, SHIP, 0};
	if (ac == 1 || (!valid_args(ac, av, &env))) 
		return (usage(av[0], &env));
	if (!(env.mlx = mlx_init()))
		return (0 * err("Could not init mlx.\n"));
	if (!(env.win = mlx_new_window(env.mlx, WIN_X, WIN_Y, WIN_NAME)))
		return (0 * err("Could not create mlx window.\n"));
	env.dimx = (t_doub2){-2., 2.};
	env.dimy = (t_doub2){-2., 2.};
	env.mouse = (t_int2){0, 0};
	draw(&env);
	mlx_key_hook(env.win, &hk, &env);
	mlx_loop(env.mlx);
	return (0);
}
