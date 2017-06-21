/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 12:26:30 by vbastion          #+#    #+#             */
/*   Updated: 2017/06/21 18:24:00 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				bckgd(t_env *e)
{
	t_int2			pos;
	t_color			c;

	pos.b = -1;
	while (++pos.b < WIN_Y)
	{
		pos.a = -1;
		while (++pos.a < WIN_X)
		{
			c.co = 0x0;
			c.c[1] = 255 * ((double)pos.a / WIN_X);
			c.c[2] = 255 * ((double)(pos.a + pos.b * WIN_X)) / (WIN_X * WIN_Y);
			c.c[0] = 255 * ((double)(pos.a + pos.b * WIN_X)) / (WIN_X * WIN_Y);
			*(img_get_addr(e, &pos)) = c.co;
		}
	}
}

int					usage(const char *name, const t_env *env)
{
	char			**fnames;

	fnames = env->fnames;
	ft_putstr("\e[31mUsage:\e[0m ");
	ft_putstr(name);
	ft_putstr("\e[32m <fractal>\e[0m\n");
	while (*fnames != NULL)
	{
		ft_putstr("\t");
		ft_putstr(*fnames);
		ft_putstr("\n");
		fnames++;
	}
	return (0);
}

int					valid_args(char **av, const t_env *env)
{
	char			**fnames;

	fnames = env->fnames;
	while (*fnames != NULL)
	{
		if (ft_strcmp(*fnames, av[1]) == 0)
			return (1);
		fnames++;
	}
	return (0);
}

int					err(const char *msg)
{
	ft_putstr_fd(msg, 2);
	return (1);
}
