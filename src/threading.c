/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 10:12:35 by vbastion          #+#    #+#             */
/*   Updated: 2017/06/06 14:46:52 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		*rdr_thread(void *pth)
{
	t_pth		*th;
	t_int2		pos;
	int			y_max;
	char		*addr;

	th = (t_pth *)pth;
	pos.a = WIN_Y / PTH_CNT * th->id - 1;
	y_max = WIN_Y / PTH_CNT * (th->id + 1);
	while (++pos.a < y_max)
	{
		pos.b = -1;
		while (++pos.b < WIN_X)
		{
			addr = th->env->img.addr + th->env->img.bpx * pos.a
					+ th->env->img.sl * pos.b;
			*((int *)addr) = th->env->renderer(th->env, &pos);
		}
	}
	return (0);
}

void			rdr_cmd(t_env *env)
{
	int			i;

	i = -1;
	img_clear(env);
	while (++i < PTH_CNT)
	{
		env->cth[i].id = i;
		env->cth[i].env = env;
		pthread_create(env->wth + i, NULL, rdr_thread, env->cth + i);
	}
	i = -1;
	while (++i < PTH_CNT)
		pthread_join(env->wth[i], NULL);
	img_to_win(env);
}
