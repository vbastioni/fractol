/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 17:09:58 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/25 17:37:34 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		draw_line(t_env *e, t_int2 *from, t_int2 *to)
{
	t_int2		curr;
	t_int2		delta;
	double		len;
	int			i;

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

static int		draw_tri(t_env *e, t_int2 *pos, int len, int depth)
{
	t_int2		lp;
	t_int2		hp;
	int			half;

	if (depth == 0)
		return (0);
	half = len / 2;
	lp = (t_int2){ pos->a - len, pos->b };
	hp = (t_int2){ pos->a - half, pos->b - sqrt(half * half + len * len) };
	draw_line(e, pos, &lp);
	draw_line(e, pos, &hp);
	draw_line(e, &hp, &lp);
	depth--;
	lp = (t_int2){ pos->a - half, pos->b };
	draw_tri(e, &lp, half, depth);
	lp = (t_int2){ pos->a - len / 4,
					pos->b - sqrt(half * half + len * len) / 2 };
	draw_tri(e, &lp, half, depth);
	lp = (t_int2){ pos->a, pos->b };
	draw_tri(e, &lp, half, depth);
	return (0);
}

int				draw_triangle(t_env *e)
{
	t_int2		init;

	init = (t_int2){WIN_X - 1, WIN_Y - 1};
	img_clear(e);
	draw_tri(e, &init, WIN_X - 100, 7);
	img_to_win(e);
	return (0);
}
