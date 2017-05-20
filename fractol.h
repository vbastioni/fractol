/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 11:12:22 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/20 14:15:14 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <mlx.h>
# include <math.h>
// #include pthread.h
# include <stdio.h> //

# include "libft.h"

# define MANDEL ("mandelbrot")
# define JULIA ("julia")
# define SHIP ("ship")

# define WIN_X (800)
# define WIN_Y (880)
# define WIN_NAME ("Fractol")

# define MAX_MOD (4.0)
# define MAX_ITER (2048)
# define LOW_ITER (32)

# define KC_EXIT (53)

# define KC_W 13
# define KC_S 1
# define KC_A 0
# define KC_D 2

# define KC_LEFT 123
# define KC_RIGHT 124
# define KC_UP 126
# define KC_DOWN 125

# define EVT_MOTION 6
# define EVT_MOTION_MASK (1L << 6)

typedef unsigned char	t_uchar;

typedef union u_color	t_color;
typedef struct s_env	t_env;
typedef struct s_cmp	t_cmp;
typedef struct s_int2	t_int2;
typedef struct s_doub2	t_doub2;
typedef struct s_img	t_img;

union					u_color
{
	t_uchar				c[4];
	int					co;
};

struct					s_cmp
{
	double				re;
	double				im;
};

struct					s_int2
{
	int					a;
	int					b;
};

struct					s_doub2
{
	double				a;
	double				b;
};

struct					s_img
{
	void				*img;
	char				*addr;
	int					bpx;
	int					sl;
	int					endian;
};

struct					s_env
{
	char				**fnames;
	t_int2				mouse;
	t_cmp				mapped_mouse;
	t_doub2				dimx;
	t_doub2				dimy;
	void				*mlx;
	void				*win;
	t_img				img;
	int					(*renderer)();
	t_uchar				params;
};

int						draw(t_env *env);

int						usage(const char *name, const t_env *env);
int						valid_args(const int ac, char **av, const t_env *env);
int						err(const char *msg);

int						color_get(double val);
int						color_smoothen(t_cmp *c, long index);

int						img_create(t_env *env);
int						img_clear(t_env *env);
int						*img_get_addr(t_env *env, t_int2 *pos);

int						expose(void *param);
int						handle_key(int kc, void *param);
int						handle_mouse(int x, int y, void *param);

#endif
