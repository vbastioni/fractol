/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 12:02:35 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/18 17:05:10 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline t_cmp	map(t_cmp *cmp, t_int2 *dims, t_env *env)
{
	cmp->re = (env->dimx.a + (env->dimx.b - env->dimx.a)
				* (double)(dims->a) / WIN_X);
	cmp->im = (env->dimy.a + (env->dimy.b - env->dimy.a)
				* (double)(dims->b) / WIN_Y);
	return (*cmp);
}

static void			do_iter(t_uchar flags, t_doub2 *tmp, t_cmp *curr, t_cmp *c, int *iter)
{
	double			twoab;

	tmp->a = curr->re * curr->re;
	tmp->b = curr->im * curr->im;
	if ((flags & 1) && curr->re == (tmp->a - tmp->b + c->re)
		&& curr->im == (2 * tmp->a * tmp->b + c->im))
		*iter = MAX_ITER - 1;
	else
	{
		twoab = 2 * ((flags & 2) ? fabs(curr->re) * fabs(curr->im) :
						curr->re * curr->im);
		curr->re = tmp->a - tmp->b + c->re;
		curr->im = twoab + c->im;
	}
	(*iter)++;
}

static int			draw_pixel(t_env *env, t_int2 *dims, t_img *img, int abs)
{
	t_cmp			curr;
	t_cmp			c;
	t_doub2			tmp;
	int				*addr;
	int				iter;

	iter = 0;
	curr = map(&c, dims, env);
	while (iter < MAX_ITER && (curr.re * curr.re + curr.im * curr.im) < MAX_MOD)
		do_iter(3, &tmp, &curr, &c, &iter);
	addr = (int *)(img->addr + img->bpx * dims->a + img->sl * dims->b);
	if (iter == MAX_ITER)
		*addr = 0x0;
	else
	{
		do_iter(2, &tmp, &curr, &c, &iter);
		if (abs)
			do_iter(2, &tmp, &curr, &c, &iter);
		*addr = color_smoothen(&curr, iter);
	}
	return (0);
}

int					draw(t_env *env)
{
	t_img			img;
	t_int2			dims;

	img.img = mlx_new_image(env->mlx, WIN_X, WIN_Y);
	img.addr = mlx_get_data_addr(img.img, &img.bpx, &img.sl, &img.endian);
	img.bpx /= 8;
	dims = (t_int2){0, 0};
	while (dims.b < WIN_Y)
	{
		dims.a = 0;
		while (dims.a < WIN_X)
		{
			draw_pixel(env, &dims, &img, 1);
			dims.a++;
		}
		dims.b++;
	}
	mlx_put_image_to_window(env->mlx, env->win, img.img, 0, 0);
	mlx_destroy_image(env->mlx, img.img);
	return (0);
}
