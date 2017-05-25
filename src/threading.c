/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 10:12:35 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/25 17:35:44 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		*rdr_thread(void *pth)
{
	t_pth		*th;
	t_int2		pos;
	int			y_max;

	th = (t_pth *)pth;
	pos.a = WIN_Y / PTH_CNT * th->id - 1;
	y_max = WIN_Y / PTH_CNT * (th->id + 1);
	while (++pos.a < y_max)
	{
		pos.b = -1;
		while (++pos.b < WIN_X)
			th->env->pixels[pos.b + pos.a * WIN_X] = th->env->renderer(th->env,
																		&pos);
	}
	return (0);
}

static void		rdr_loop(t_env *env)
{
	t_int2		pos;

	img_clear(env);
	pos.a = -1;
	while (++pos.a < WIN_Y)
	{
		pos.b = -1;
		while (++pos.b < WIN_X)
			*(img_get_addr(env, &pos)) = env->pixels[pos.b + pos.a * WIN_X];
	}
	img_to_win(env);
}

void			rdr_cmd(t_env *env)
{
	int			i;

	i = -1;
	while (++i < PTH_CNT)
	{
		env->cth[i].id = i;
		env->cth[i].env = env;
		pthread_create(env->wth + i, NULL, rdr_thread, env->cth + i);
	}
	i = -1;
	while (++i < PTH_CNT)
		pthread_join(env->wth[i], NULL);
	rdr_loop(env);
}
