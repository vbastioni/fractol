/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 17:36:06 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/25 17:36:07 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_line(t_env *env, t_int2 *from, t_int2 *to)
{
	t_int2		inter;
	t_int2		curr;
	float		len;
	int			i;

	inter.a = (to->a - from->a);
	inter.b = (to->b - from->b);
	len = sqrt(inter.a * inter.a + inter.b * inter.b);
	if (len == 0)
		return ;
	i = 0;
	while (i <= len)
	{
		curr.a = from->a + (int)inter.a * (i / len);
		curr.b = from->b + (int)inter.b * (i / len);
		if (!(curr.a >= WIN_X || curr.a < 0 || curr.b < 0 || curr.b >= WIN_Y))
			*(img_get_addr(env, &curr)) = 0xFFFFFF;
		i++;
	}
}

static int	get_points(t_env *env, t_int2 *from, float angle, float len)
{
	t_int2		to;

	to.a = from->a - cos(angle * TO_RAD) * len;
	to.b = from->b - sin(angle * TO_RAD) * len;
	draw_line(env, from, &to);
	len *= env->tree_step;
	if (len > env->tree_min_len)
	{
		get_points(env, &to, angle + 45, len);
		get_points(env, &to, angle - 45, len);
	}
	return (0);
}

int			draw_tree(t_env *env)
{
	t_int2	init;

	img_clear(env);
	init = (t_int2){WIN_X / 2, WIN_Y - 1};
	get_points(env, &init, 90, DEF_TREE_LEN);
	img_to_win(env);
	return (1);
}
