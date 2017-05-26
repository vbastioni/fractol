/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 12:31:30 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/25 17:44:54 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		move(int kc, t_env *e)
{
	t_doub2		delta;

	delta.a = (e->dimx.b - e->dimx.a) * .1;
	delta.b = (e->dimy.b - e->dimy.a) * .1;
	if (kc == KC_D || kc == KC_RIGHT)
		e->dimx = (t_doub2){ e->dimx.a + delta.a, e->dimx.b + delta.b };
	else if (kc == KC_A || kc == KC_LEFT)
		e->dimx = (t_doub2){ e->dimx.a - delta.a, e->dimx.b - delta.b };
	else if (kc == KC_S || kc == KC_DOWN)
		e->dimy = (t_doub2){ e->dimy.a + delta.a, e->dimy.b + delta.b };
	else if (kc == KC_W || kc == KC_UP)
		e->dimy = (t_doub2){ e->dimy.a - delta.a, e->dimy.b - delta.b };
	(e->fid > 3) ? e->renderer(e) : rdr_cmd(e);
	return (1);
}

int				reset(t_env *e)
{
	e->dimx = e->def_dimx;
	e->dimy = e->def_dimy;
	(e->fid > 3) ? e->renderer(e) : rdr_cmd(e);
	return (0);
}

int				change_mode(t_env *e)
{
	if (e->fid != 4)
		return (0);
	e->newton_mode++;
	if (e->newton_mode > 3)
		e->newton_mode = 0;
	(e->fid > 3) ? e->renderer(e) : rdr_cmd(e);
	return (1);
}

int				swap_color(t_env *e)
{
	e->color_scale_id++;
	if (e->color_scale_id == COL_GRAD_CNT)
		e->color_scale_id = 0;
	(e->fid > 3) ? e->renderer(e) : rdr_cmd(e);
	return (0);
}

int				handle_key(int kc, void *param)
{
	t_env		*e;

	e = (t_env *)param;
	if (kc == KC_EXIT)
		exit(0);
	if (kc == KC_LEFT || kc == KC_A || kc == KC_RIGHT || kc == KC_D
			|| kc == KC_DOWN || kc == KC_S || kc == KC_UP || kc == KC_W)
		move(kc, e);
	if (kc == KC_SPACE)
		change_mode(e);
	if (kc == KC_R)
		reset(e);
	if (kc == KC_TAB)
		swap_color(e);
	return (0);
}

int				handle_mouse(int x, int y, void *param)
{
	t_env *e;

	e = (t_env *)param;
	if (e->fid != 1 || (e->params & 8) == 0 || x < 0 || y < 0
		|| x > WIN_X || y > WIN_Y)
		return (0);
	e->mouse = (t_int2){x, y};
	(e->fid > 3) ? e->renderer(e) : rdr_cmd(e);
	return (0);
}

int				handle_mouse_btn(int btn, int x, int y, void *param)
{
	t_env		*e;
	t_doub2		d;

	return (0);
	if (btn > 5)
		return (0);
	e = (t_env *)param;
	d.a = ((double)x / WIN_X) * (e->dimx.b - e->dimx.a);
	e->dimx.a += d.a * (btn == 4 ? -1 : 1);
	e->dimx.b += d.a * (btn == 4 ? -1 : 1);
	d.b = ((double)y / WIN_Y) * (e->dimy.b - e->dimy.a);
	e->dimy.a += d.b * (btn == 4 ? -1 : 1);
	e->dimy.b += d.b * (btn == 4 ? -1 : 1);
	e->renderer(e);
	if (btn == 4)
	{
	}
	else if (btn == 5)
	{
	}
	return (0);
}

int				expose(void *param)
{
	t_env		*e;

	e = (t_env *)param;
	(e->fid > 3) ? e->renderer(e) : rdr_cmd(e);
	return (0);
}
