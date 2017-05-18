/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 12:02:35 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/18 16:50:54 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline void	map(t_cmp *cmp, t_int2 *dims, t_env *env)
{
	cmp->re = (env->dimx.a + (env->dimx.b - env->dimx.a)
				* (double)(dims->a) / WIN_X);
	cmp->im = (env->dimy.a + (env->dimy.b - env->dimy.a)
				* (double)(dims->b) / WIN_Y);
}

int					color_get(int val)
{
	const double	*scales[3] = (const double *[3]) {
		(const double[2]){0., 1.},
		(const double[2]){0.33, 1.},
		(const double[2]){1., 1.}
	};
	t_color			c;
	double			de;

	de = (double)val / MAX_ITER;
	c.co = 0;
	c.c[2] = (scales[0][0] + (scales[0][1] - scales[0][0]) * de) * 0xFF * 100;
	c.c[1] = (scales[1][0] + (scales[1][1] - scales[1][0]) * de) * 0xFF * 100;
	c.c[0] = (scales[2][0] + (scales[2][1] - scales[2][0]) * de) * 0xFF * 100;
	return (c.co);
}

static int			draw_pixel(t_env *env, t_int2 *dims, t_img *img)
{
	t_cmp			curr;
	t_cmp			c;
	t_doub2			tmp;
	int				*addr;
	double			twoab;
	int				iter;

	iter = 0;
	map(&c, dims, env);
	curr = c;
	while (iter < MAX_ITER && (((tmp.a = curr.re * curr.re)
								+ (tmp.b = curr.im * curr.im)) < MAX_MOD))
	{
		if (curr.re == (tmp.a - tmp.b + c.re) && twoab == (2 * tmp.a * tmp.b))
			iter = MAX_ITER - 1;
		twoab = 2 * curr.re * curr.im;
		curr.re = tmp.a - tmp.b + c.re;
		curr.im = twoab + c.im;
		iter++;
	}
	addr = (int *)(img->addr + img->bpx * dims->a + img->sl * dims->b);
	*addr = iter == MAX_ITER ? 0x0 : color_get(iter);
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
			draw_pixel(env, &dims, &img);
			dims.a++;
		}
		dims.b++;
	}
	mlx_put_image_to_window(env->mlx, env->win, img.img, 0, 0);
	mlx_destroy_image(env->mlx, img.img);
	return (0);
}
