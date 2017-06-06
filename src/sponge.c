/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sponge.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 17:10:14 by vbastion          #+#    #+#             */
/*   Updated: 2017/06/06 15:51:58 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void			draw_line(t_env *e, t_int2 *from, t_int2 *to, int level)
{
	t_int2			curr;
	t_int2			delta;
	double			len;
	int				i;

	i = 0;
	delta = (t_int2){to->a - from->a, to->b - from->b};
	len = sqrt(delta.a * delta.a + delta.b * delta.b);
	if (len == 0)
		return ;
	while (i < len)
	{
		curr.a = from->a + (int)(delta.a * i / len);
		curr.b = from->b + (int)(delta.b * i / len);
		if (!(curr.a >= WIN_X || curr.a < 0 || curr.b >= WIN_Y || curr.b < 0))
			*(img_get_addr(e, &curr)) = color_scale_get((double)level /
														e->sponge_depth,
														e);
		i++;
	}
}

void				draw_child(t_env *e, int level, t_int2 *dims, double delta)
{
	t_int2			dms;

	dms = (t_int2){
		dims->a - delta * 2,
		dims->b + delta * 2
	};
	draw_cube(e, level, &dms, delta);
	dms = (t_int2){dims->a, dims->b + delta * 2};
	draw_cube(e, level, &dms, delta);
	dms = (t_int2){dims->a + delta * 2, dims->b + delta * 2};
	draw_cube(e, level, &dms, delta);
	dms = (t_int2){dims->a + delta * 2, dims->b};
	draw_cube(e, level, &dms, delta);
	dms = (t_int2){dims->a + delta * 2, dims->b - delta * 2};
	draw_cube(e, level, &dms, delta);
	dms = (t_int2){dims->a, dims->b - delta * 2};
	draw_cube(e, level, &dms, delta);
	dms = (t_int2){dims->a - delta * 2, dims->b - delta * 2};
	draw_cube(e, level, &dms, delta);
	dms = (t_int2){dims->a - delta * 2, dims->b};
	draw_cube(e, level, &dms, delta);
}

void				draw_cube(t_env *e, int level, t_int2 *dims, double r)
{
	t_int2			pos[4];
	int				delta;

	if (level >= e->sponge_depth)
		return ;
	delta = (int)(r / 3 + .5);
	pos[0] = (t_int2){dims->a - delta - 1 + e->delta.a,
						dims->b - delta - 1 + e->delta.b};
	pos[1] = (t_int2){dims->a + delta - 1 + e->delta.a,
						dims->b - delta - 1 + e->delta.b};
	pos[2] = (t_int2){dims->a + delta - 1 + e->delta.a,
						dims->b + delta - 1 + e->delta.b};
	pos[3] = (t_int2){dims->a - delta - 1 + e->delta.a,
						dims->b + delta - 1 + e->delta.b};
	draw_line(e, pos, pos + 1, level);
	draw_line(e, pos + 1, pos + 2, level);
	draw_line(e, pos + 2, pos + 3, level);
	draw_line(e, pos + 3, pos, level);
	draw_child(e, level + 1, dims, delta);
}

int					draw_sponge(t_env *e)
{
	t_int2			dims;

	dims = (t_int2){WIN_X / 2, WIN_Y / 2};
	img_clear(e);
	bckgd(e);
	draw_cube(e, 0, &dims, (WIN_X / 2) * e->zoom);
	img_to_win(e);
	return (0);
}
