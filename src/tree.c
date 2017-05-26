/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 17:36:06 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/26 14:35:26 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline void	mouse_map(t_env *e, t_doub2 *pos)
{
	pos->a = e->mouse.a / (double)WIN_X;
	pos->b = e->mouse.b / (double)WIN_Y;
}

static void			draw_line(t_env *e, t_int2 *from, t_int2 *to)
{
	t_int2			inter;
	t_int2			curr;
	float			len;
	int				i;

	inter.a = (to->a - from->a);
	inter.b = (to->b - from->b);
	len = sqrt(inter.a * inter.a + inter.b * inter.b);
	if (len == 0)
		return ;
	i = 0;
	while (i <= len)
	{
		curr.a = from->a + (inter.a * (i / len) + 0.5);
		curr.b = from->b + (inter.b * (i / len) + 0.5);
		if (!(curr.a >= WIN_X || curr.a < 0 || curr.b < 0 || curr.b >= WIN_Y))
			*(img_get_addr(e, &curr)) = color_scale_get((i / len) / 255, e);
		i++;
	}
}

static int			get_points(t_env *e, t_int2 *from, float angle, float len)
{
	t_int2			to;
	t_doub2			pos;

	mouse_map(e, &pos);
	to.a = from->a - cos(angle * TO_RAD) * len;
	to.b = from->b - sin(angle * TO_RAD) * len;
	draw_line(e, from, &to);
	len *= e->tree_step;
	if (len > e->tree_min_len)
	{
		get_points(e, &to, angle + 45 * pos.a, len);
		get_points(e, &to, angle - 45 * pos.b, len);
	}
	return (0);
}

int					draw_tree(t_env *e)
{
	t_int2			init;

	img_clear(e);
	bckgd(e);
	init = (t_int2){WIN_X / 2, WIN_Y - 1};
	get_points(e, &init, 90, e->tree_len);
	img_to_win(e);
	return (1);
}
