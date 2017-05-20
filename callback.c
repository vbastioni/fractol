/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 12:31:30 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/20 17:39:10 by vbastion         ###   ########.fr       */
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

int				reset(t_env *env)
{
	env->dimx = env->def_dimx;
	env->dimy = env->def_dimy;
	env->renderer(env);
	return (0);
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
	if (kc == KC_R)
		reset(env);
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

int				handle_mouse_btn(int btn, int x, int y, void *param)
{
	t_env		*env;
	t_doub2		d;

	if (btn > 5)
		return (0);
	env = (t_env *)param;
	d.a = ((double)x / WIN_X) * (env->dimx.b - env->dimx.a);
	env->dimx.a += d.a * (btn == 4 ? -1 : 1);
	env->dimx.b += d.a * (btn == 4 ? -1 : 1);
	d.b = ((double)y / WIN_Y) * (env->dimy.b - env->dimy.a);
	env->dimy.a += d.b * (btn == 4 ? -1 : 1);
	env->dimy.b += d.b * (btn == 4 ? -1 : 1);
	printf("d:[%f, %f]\n", d.a, d.b);
	env->renderer(env);
	if (btn == 4)
	{
	}
	else if (btn == 5)
	{
		//
	}
	return (0);
}

int				expose(void *param)
{
	t_env *		env;

	env = (t_env *)param;
	env->renderer(env);
	return (0);
}
