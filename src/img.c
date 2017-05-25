/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 11:40:23 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/25 17:30:25 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			img_create(t_env *env)
{
	if ((env->img.img = mlx_new_image(env->mlx, WIN_X, WIN_Y)) == NULL)
		return (0 * err("Could not create image\n"));
	else if ((env->img.addr = mlx_get_data_addr(env->img.img, &env->img.bpx,
												&env->img.sl, &env->img.endian))
				== NULL)
		return (0 * err("Could not get img data address\n"));
	env->img.bpx /= 8;
	return (1);
}

int			img_clear(t_env *env)
{
	int		pos;
	int		max;

	pos = 0;
	max = WIN_X * WIN_Y;
	while (pos < max)
	{
		*(env->img.addr) = 0;
		pos += env->img.bpx;
	}
	return (1);
}

int			*img_get_addr(t_env *env, t_int2 *pos)
{
	return ((int *)(env->img.addr + env->img.bpx * pos->a
					+ env->img.sl * pos->b));
}

int			img_to_win(t_env *env)
{
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}
