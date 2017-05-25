/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sponge.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 17:10:14 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/25 17:34:53 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_line(t_env *e, t_int2 *from, t_int2 *to)
{
	t_int2	curr;
	t_int2	delta;
	double	len;
	int		i;

	i = 0;
	delta = (t_int2){ to->a - from->a, to->b - from->b };
	len = sqrt(delta.a * delta.a + delta.b * delta.b);
	if (len == 0)
		return ;
	while (i < len)
	{
		curr.a = from->a + (int)(delta.a * i / len);
		curr.b = from->b + (int)(delta.b * i / len);
		if (!(curr.a >= WIN_X || curr.a < 0 || curr.b >= WIN_Y || curr.b < 0))
			*(img_get_addr(e, &curr)) = 0xFFFFFF;
		i++;
	}
}

static void	draw_cube(t_env *e, int level, t_dims *dims, double r)
{
	t_int2		pos[4];
	double		delta;

	if (level >= e->sponge_depth)
		return ;
	delta = r / 3;
	pos[0] = (t_int2){ dims->a - delta - 1, dims->b - delta - 1 };
	pos[1] = (t_int2){ dims->a + delta - 1, dims->b - delta - 1 };
	pos[2] = (t_int2){ dims->a + delta - 1, dims->b + delta - 1 };
	pos[3] = (t_int2){ dims->a - delta - 1, dims->b + delta - 1 };
	draw_line(e, pos, pos + 1);
	draw_line(e, pos + 1, pos + 2);
	draw_line(e, pos + 2, pos + 3);
	draw_line(e, pos + 3, pos);
	draw_cube(e, ++level, dims->a - delta * 2, dims->b + delta * 2, r / 3);
	draw_cube(e, level, dims->a, dims->b + delta * 2, delta);
	draw_cube(e, level, dims->a + delta * 2, dims->b + delta * 2, delta);
	draw_cube(e, level, dims->a + delta * 2, dims->b, delta);
	draw_cube(e, level, dims->a + delta * 2, dims->b - delta * 2, delta);
	draw_cube(e, level, dims->a, dims->b - delta * 2, delta);
	draw_cube(e, level, dims->a - delta * 2, dims->b - delta * 2, delta);
	draw_cube(e, level, dims->a - delta * 2, dims->b, delta);
}

int			draw_sponge(t_env *e)
{
	t_int2		dims;

	dims = (t_int2){WIN_X / 2, WIN_Y / 2};
	img_clear(e);
	e->sponge_depth = 6;
	draw_cube(e, 0, &dims, 600.);
	img_to_win(e);
	return (0);
}
