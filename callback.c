/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 12:31:30 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/20 14:14:19 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		move(int kc, t_env *env)
{
	t_doub2		delta;

	delta.a = (env->dimx.b - env->dimx.a) * .1;
	delta.b = (env->dimy.b - env->dimy.a) * .1;
	if (kc == KC_D || kc == KC_RIGHT)
	{
		env->dimx.a += delta.a;
		env->dimx.b += delta.a;
	}
	else if (kc == KC_A || kc == KC_LEFT)
	{
		env->dimx.a -= delta.a;
		env->dimx.b -= delta.a;
	}
	else if (kc == KC_S || kc == KC_DOWN)
	{
		env->dimy.a += delta.a;
		env->dimy.b += delta.a;
	}
	else if (kc == KC_W || kc == KC_UP)
	{
		env->dimy.a -= delta.a;
		env->dimy.b -= delta.a;
	}
	draw(env);
	return (1);
}

int				handle_key(int kc, void *param)
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

int				handle_mouse(int x, int y, void *param)
{
	t_env *env;

	env = (t_env *)param;
	if ((env->params & 8) == 0 || x < 0 || y < 0 || x > WIN_X || y > WIN_Y)
		return (0);
	env->mouse = (t_int2){x, y};
	draw(env);
	return (0);
}

int				expose(void *param)
{
	t_env *		env;

	env = (t_env *)param;
	env->renderer(env);
	return (0);
}
