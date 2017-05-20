/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 12:02:35 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/20 10:44:29 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	FLAGS VALUES:
**		1:	LOW_DEF
**		2:	abs c
**		4:	break early (optimisation)
*/

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
	if ((flags & 4) && curr->re == (tmp->a - tmp->b + c->re)
		&& curr->im == (2 * tmp->a * tmp->b + c->im))
		*iter = ((flags & 1) ? LOW_ITER : MAX_ITER) - 1;
	else
	{
		twoab = 2 * ((flags & 2) ? fabs(curr->re) * fabs(curr->im) :
						curr->re * curr->im);
		curr->re = tmp->a - tmp->b + c->re;
		curr->im = twoab + c->im;
	}
	(*iter)++;
}

static int			draw_pixel(t_env *env, t_int2 *dims, t_img *img,
								t_uchar flags)
{
	t_cmp			curr;
	t_cmp			c;
	t_doub2			tmp;
	int				*addr;
	int				iter;

	iter = 0;
	curr = map(&c, dims, env);
	while (iter < ((flags & 1) ? LOW_ITER : MAX_ITER)
			&& (curr.re * curr.re + curr.im * curr.im) < MAX_MOD)
		do_iter(flags, &tmp, &curr, &c, &iter);
	addr = (int *)(img->addr + img->bpx * dims->a + img->sl * dims->b);
	if (iter == (flags & 1) ? LOW_ITER : MAX_ITER)
		*addr = 0x0;
	else
	{
		do_iter((flags & 0xB), &tmp, &curr, &c, &iter);
		if ((flags & 2))
			do_iter((flags & 0xB), &tmp, &curr, &c, &iter);
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
			draw_pixel(env, &dims, &img, 0);
			dims.a++;
		}
		dims.b++;
	}
	mlx_put_image_to_window(env->mlx, env->win, img.img, 0, 0);
	mlx_destroy_image(env->mlx, img.img);
	return (0);
}
