/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 10:12:35 by vbastion          #+#    #+#             */
/*   Updated: 2017/06/21 15:44:57 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		handle_th_cr_err(int err, t_env *env, int i)
{
	int			id;

	id = 0;
	if (err == 11)
		ft_putstr_fd("Insufficient resources to create thread\n", 2);
	else if (err == 22)
		ft_putstr_fd("Invalid setting of attr.\n", 2);
	else if (err == 1)
		ft_putstr_fd("None of permissions needed.\n", 2);
	while (id < i)
	{
		pthread_detach(env->wth[id]);
		id++;
	}
	cb_exit(env);
}

static void		handle_th_join_err(int err, t_env *env, int i)
{
	if (err == 35)
		ft_putstr_fd("A Deadlock was detected.\n", 2);
	else if (err == 22)
		ft_putstr_fd("thread is not a joinable thread", 2);
	else if (err == 3)
		ft_putstr_fd("No thread with this id could be found.\n", 2);
	while (i < PTH_CNT)
	{
		pthread_detach(env->wth[i]);
		i++;
	}
	cb_exit(env);
}

static void		*rdr_thread(void *pth)
{
	t_pth		*th;
	t_int2		pos;
	int			y_max;
	char		*addr;

	th = (t_pth *)pth;
	pos.a = WIN_Y / PTH_CNT * th->id;
	y_max = WIN_Y / PTH_CNT * (th->id + 1);
	while (pos.a < y_max)
	{
		pos.b = 0;
		while (pos.b < WIN_X)
		{
			addr = th->env->img.addr + th->env->img.bpx * pos.a
					+ th->env->img.sl * pos.b;
			*((int *)addr) = th->env->renderer(th->env, &pos);
			pos.b++;
		}
		pos.a++;
	}
	return (0);
}

void			prep_threads(t_env *env)
{
	int			i;

	i = 0;
	while (i < PTH_CNT)
	{
		env->cth[i].id = i;
		env->cth[i].env = env;
		i++;
	}
}

void			rdr_cmd(t_env *env)
{
	int			i;
	int			err;

	i = 0;
	img_clear(env);
	while (i < PTH_CNT)
	{
		err = pthread_create(env->wth + i, NULL, rdr_thread, env->cth + i);
		if (err != 0)
			handle_th_cr_err(err, env, i);
		i++;
	}
	i = 0;
	while (i < PTH_CNT)
	{
		if ((err = pthread_join(env->wth[i], NULL)) != 0)
			handle_th_join_err(err, env, i);
		i++;
	}
	img_to_win(env);
}
