/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 17:09:58 by vbastion          #+#    #+#             */
/*   Updated: 2017/06/05 12:31:14 by vbastion         ###   ########.fr       */
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
		curr.a = from->a + (int)(delta.a * (double)i / len + 0.5);
		curr.b = from->b + (int)(delta.b * (double)i / len + 0.5);
		if (!(curr.a >= WIN_X || curr.a < 0 || curr.b >= WIN_Y || curr.b < 0))
			*(img_get_addr(e, &curr)) = 0xFFFFFF;
		i++;
	}
}

static void		draw_interior(t_env *e, t_int2 abc[3], int depth)
{
	t_int2		la;
	t_int2		lb;
	t_int2		lc;
	t_int2		*arr;

	depth--;
	if (depth == 0)
		return ;
	la = (t_int2){ (abc[1].a - abc[0].a) / 2 + abc[0].a,
					(abc[1].b - abc[0].b) / 2 + abc[0].b };
	lb = (t_int2){ (abc[1].a - abc[2].a) / 2 + abc[2].a,
					(abc[2].b - abc[1].b) / 2 + abc[1].b };
	lc = (t_int2){ (abc[2].a - abc[0].a) / 2 + abc[0].a,
					(abc[2].b - abc[0].b) / 2 + abc[0].b };
	draw_line(e, &la, &lb);
	draw_line(e, &lb, &lc);
	draw_line(e, &lc, &la);
	arr = (t_int2[3]){ abc[0], la, lc };
	draw_interior(e, arr, depth);
	arr = (t_int2[3]){ la, abc[1], lb };
	draw_interior(e, arr, depth);
	arr = (t_int2[3]){ lb, lc, abc[2] };
	draw_interior(e, arr, depth);
}

int				draw_triangle(t_env *e)
{
	t_int2		*abc;

	if (e->tri_depth == 0)
		return (0);
	abc = (t_int2[3]){
		(t_int2){ WIN_X - 1, WIN_Y - 1 },
		(t_int2){ 0, WIN_Y - 1 },
		(t_int2){ (int)((double)WIN_X / 2), 0 }
	};
	img_clear(e);
	bckgd(e);
	draw_line(e, abc, abc + 1);
	draw_line(e, abc + 1, abc + 2);
	draw_line(e, abc + 2, abc);
	draw_interior(e, abc, e->tri_depth);
	img_to_win(e);
	return (0);
}
