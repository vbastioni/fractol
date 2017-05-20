/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 12:26:30 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/20 12:30:08 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				usage(const char *name, const t_env *env)
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

int				valid_args(const int ac, char **av, const t_env *env)
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

#endif
