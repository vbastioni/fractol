#include "fractol.h"

void		*rdr_thread(void *pth)
{
	t_pth		*th;
	t_int2		pos;
	int			y_max;

	th = (t_thread *)pth;
	pos.a = WIN_Y / PTH_CNT * th->id - 1;
	y_max = WIN_Y / PTH_CNT * (th->id + 1);
	while (++pos.a < y_max)
	{
		pos.b = -1;
		while (++pos.b < WIN_X)
			env->pixel[pos.b + pos.a * WIN_X] = env->rdr(env, &pos);
		}
	}
}

void		rdr_cmd(t_env *env)
{	
	int			i;

	i = -1;
	while (++i < PTH_CNT)
	{
		env->cth[i].id = i;
		env->cth[i].env = env;
		pthread_create(env->wth + i, NULL, rdr_thread, env->cth + i);
	}
	i = -1;
	while (++i < PTH_CNT)
		pthread_join(r->threads[i], NULL);
	rdr_loop(env);
}

void		rdr_loop(t_env *env)
{
	t_int2		pos;

	img_clear(env);
	pos.a = -1;
	while (++pos.a < WIN_Y)
	{
		pos.b = -1;
		while (++pos.b < WIN_X)
			*(img_get_addr(env, &pos)) = env->pixel[pos.y + pos.x * WIN_X];
	}
	img_to_win(env);
}
