/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 11:12:22 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/25 11:29:18 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <mlx.h>
# include <math.h>
#include <pthread.h>
# include <stdio.h> //

# include "libft.h"

# define DEBUG (1)

# define MANDEL ("mandelbrot")
# define JULIA ("julia")
# define SHIP ("ship")
# define TREE ("tree")
# define NEWTON ("newton")
# define TRIANGLE ("triangle")
# define SPONGE ("sponge")

# define WIN_X (800)
# define WIN_Y (800)
# define WIN_NAME ("Fractol")
# define PTH_CNT (4)

# define DEF_TREE_LEN (200)

/*
**	NEWTON's variables
*/

# define N_MAX_CNT (255)
# define N_MULT_COL (15)
# define N_TOL (.0001)

# ifdef PI
#  undef PI
# endif
# define PI (3.14159265358979323846)
# define TO_RAD (0.01745329251994329577)

# define MAX_MOD (4.)
# define MAX_ITER (2048)
# define LOW_ITER (128)

# define KC_EXIT (53)

# define KC_W 13
# define KC_S 1
# define KC_A 0
# define KC_D 2

# define KC_R 15

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
typedef struct s_pth	t_pth;
typedef struct s_rdr	t_rdr;

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

struct					s_pth
{
	int					id;
	t_env				*env;
};

struct					s_env
{
	char				**fnames;
	t_int2				mouse;
	t_cmp				mapped_mouse;
	t_doub2				def_dimx;
	t_doub2				def_dimy;
	t_doub2				dimx;
	t_doub2				dimy;
	void				*mlx;
	void				*win;
	t_img				img;
	int					*pixels;
	int					(*renderer)();
	pthread_t			wth[PTH_CNT];
	t_pth				cth[PTH_CNT];
	t_uchar				params;
	int					newton_mode;
	float				tree_step;
	float				tree_min_len;
	int					sponge_depth;
	t_cmp				r[3];
};

int						draw_mandel(t_env *env, t_int2 *pos);
int						draw_tree(t_env *env);
int						draw_newton(t_env *env, t_int2 *pos);
int						draw_sponge(t_env *env);
int						draw_triangle(t_env *env);

int						usage(const char *name, const t_env *env);
int						valid_args(const int ac, char **av, const t_env *env);
int						err(const char *msg);

int						color_get(double val);
int						color_smoothen(t_cmp *c, long index);

int						img_create(t_env *env);
int						img_clear(t_env *env);
int						*img_get_addr(t_env *env, t_int2 *pos);
int						img_to_win(t_env *env);

int						expose(void *param);
int						handle_key(int kc, void *param);
int						handle_mouse(int x, int y, void *param);
int						handle_mouse_btn(int btn, int x, int y, void *param);

void					rdr_cmd(t_env *env);

/*
**	Complex numbers functions
**	Somewhat of an operator overload for C
*/

double					cmp_abs(const t_cmp *cmp);
t_cmp					cmp_mult(const t_cmp *lhs, const t_cmp *rhs);
t_cmp					cmp_sub(const t_cmp *lhs, const t_cmp *rhs);
t_cmp					cmp_div(const t_cmp *lhs, const t_cmp *rhs);
t_cmp					cmp_multr(const t_cmp *lhs, double r);

#endif
