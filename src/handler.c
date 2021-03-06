/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 15:56:36 by vbastion          #+#    #+#             */
/*   Updated: 2017/06/21 18:12:18 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		move(int kc, t_env *e)
{
	t_doub2		delta;

	delta.a = (e->dimx.b - e->dimx.a) * .1;
	delta.b = (e->dimy.b - e->dimy.a) * .1;
	if (kc == KC_D || kc == KC_RIGHT)
		e->delta.a += .1 * e->zoom;
	else if (kc == KC_A || kc == KC_LEFT)
		e->delta.a -= .1 * e->zoom;
	else if (kc == KC_S || kc == KC_DOWN)
		e->delta.b += .1 * e->zoom;
	else if (kc == KC_W || kc == KC_UP)
		e->delta.b -= .1 * e->zoom;
	(e->fid > 3) ? e->renderer(e) : rdr_cmd(e);
	return (1);
}

static int		change_fract(t_env *e, int kc)
{
	if (kc == KC_1)
		env_set_mandel(e, 0);
	else if (kc == KC_2)
		env_set_mandel(e, 1);
	else if (kc == KC_3)
		env_set_mandel(e, 2);
	else if (kc == KC_4)
		env_set_tree(e);
	else if (kc == KC_5)
		env_set_newton(e);
	else if (kc == KC_6)
		env_set_triangle(e);
	else if (kc == KC_7)
		env_set_sponge(e);
	else if (kc == KC_8)
		env_set_mandel(e, 3);
	(e->fid > 3) ? e->renderer(e) : rdr_cmd(e);
	return (0);
}

int				handle_key(int kc, void *param)
{
	t_env		*e;

	e = (t_env *)param;
	if (kc == KC_EXIT)
		cb_exit(e);
	if (kc == KC_LEFT || kc == KC_A || kc == KC_RIGHT || kc == KC_D
			|| kc == KC_DOWN || kc == KC_S || kc == KC_UP || kc == KC_W)
		move(kc, e);
	if (kc == KC_SPACE)
		change_mode(e);
	if (kc == KC_R)
		reset(e);
	if (kc == KC_TAB)
		swap_color(e);
	if (kc == KC_Q || kc == KC_E)
		cb_qe(kc == KC_E, e);
	if (kc == KC_1 || kc == KC_2 || kc == KC_3 || kc == KC_4 || kc == KC_5
		|| kc == KC_6 || kc == KC_7 || kc == KC_8)
		change_fract(e, kc);
	return (0);
}

int				handle_mouse(int x, int y, void *param)
{
	t_env *e;

	e = (t_env *)param;
	if (x < 0 || y < 0 || x > WIN_X || y > WIN_Y)
		return (0);
	if ((e->fid == 1 && (e->params & 8) == 0) || !(e->fid == 1 || e->fid == 4))
		return (0);
	e->mouse = (t_int2){x, y};
	(e->fid > 3) ? e->renderer(e) : rdr_cmd(e);
	return (0);
}

int				handle_mouse_btn(int btn, int x, int y, void *param)
{
	t_env		*e;

	if (btn < 4 && btn > 7)
		return (0);
	e = (t_env *)param;
	zoom(x, y, e, (btn == 6 || btn == 4) ? ZOOM : (1 / ZOOM));
	return (0);
}
