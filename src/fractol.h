/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 11:12:22 by vbastion          #+#    #+#             */
/*   Updated: 2017/06/06 16:41:03 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <pthread.h>

# include "libft.h"

# define DEBUG (1)

# define MANDEL ("mandelbrot")
# define JULIA ("julia")
# define SHIP ("ship")
# define TREE ("tree")
# define NEWTON ("newton")
# define TRIANGLE ("triangle")
# define SPONGE ("sponge")

# define WIN_X (480)
# define WIN_Y (480)
# define WIN_NAME ("Fractol")
# define PTH_CNT (4)
# define ZOOM (1.1)

# define COL_GRAD_CNT (4)

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
# define ITER (128)

# define KC_EXIT (53)

# define KC_SPACE (49)
# define KC_TAB (48)

# define KC_1 18
# define KC_2 19
# define KC_3 20
# define KC_4 21
# define KC_5 23
# define KC_6 22
# define KC_7 26
# define KC_8 28

# define KC_W 13
# define KC_S 1
# define KC_A 0
# define KC_D 2
# define KC_Q 12
# define KC_E 14
# define KC_O 31
# define KC_P 35

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
	t_doub2				delta;
	double				zoom;
	t_doub2				dimx;
	t_doub2				dimy;
	void				*mlx;
	void				*win;
	t_img				img;
	int					(*renderer)();
	pthread_t			wth[PTH_CNT];
	t_pth				cth[PTH_CNT];
	t_uchar				params;
	int					z_iter;
	int					newton_mode;
	float				tree_step;
	float				tree_min_len;
	int					sponge_depth;
	int					tri_depth;
	int					(*col_getter[COL_GRAD_CNT])();
	int					color_scale_id;
	int					tree_len;
	int					fid;
	t_cmp				r[3];
};

/*
**	DRAWERS
*/

int						draw_mandel(t_env *e, t_int2 *pos);
int						draw_tree(t_env *e);
int						draw_newton(t_env *e, t_int2 *pos);
int						draw_sponge(t_env *e);
int						draw_triangle(t_env *e);

void					draw_child(t_env *e, int level, t_int2 *dims,
									double delta);
void					draw_cube(t_env *e, int level, t_int2 *dims, double r);

/*
**	UTILITY
*/

int						usage(const char *name, const t_env *e);
int						valid_args(const int ac, char **av, const t_env *e);
int						err(const char *msg);

void					zoom(int x, int y, t_env *e, double z);
int						clamp(int val, int min, int max);
void					bckgd(t_env *e);

/*
**	COLOR HANDLING
*/

int						color_get_copper(double val);
int						color_get_bones(double val);
int						color_get_blue(double val);
int						color_get_gum(double val);

int						color_scale_get(double progress, const t_env *e);
int						color_smoothen(t_cmp *c, long index, t_env *e);

/*
**	IMG WORK
*/

int						img_create(t_env *e);
int						img_clear(t_env *e);
int						*img_get_addr(t_env *e, t_int2 *pos);
int						img_to_win(t_env *e);

/*
**	CALLBACKS
*/

int						expose(void *param);
int						handle_key(int kc, void *param);
int						handle_mouse(int x, int y, void *param);
int						handle_mouse_btn(int btn, int x, int y, void *param);

int						cb_qe(int fwd, t_env *e);
int						cb_exit(t_env *e);

int						reset(t_env *e);
int						change_mode(t_env *e);
int						swap_color(t_env *e);

void					rdr_cmd(t_env *e);
void					prep_threads(t_env *e);

/*
**	PREPARATION
*/

void					env_set_mandel(t_env *e, int id);
void					env_set_tree(t_env *e);
void					env_set_newton(t_env *e);
void					env_set_sponge(t_env *e);
void					env_set_triangle(t_env *e);

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
