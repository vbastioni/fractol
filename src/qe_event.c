/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qe_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 15:49:49 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/26 15:52:36 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline int	tree_change_len(t_env *e, int fwd)
{
	int			prev;

	prev = e->tree_len;
	e->tree_len = clamp(e->tree_len + 10 * (fwd ? 1 : -1), 0, 350);
	if (e->tree_len != prev)
		e->renderer(e);
	return (0);
}

static inline int	sponge_change_depth(t_env *e, int fwd)
{
	int			prev;

	prev = e->sponge_depth;
	e->sponge_depth = clamp(e->sponge_depth + (fwd ? 1 : -1), 0, 8);
	if (e->sponge_depth != prev)
		e->renderer(e);
	return (0);
}

int					cb_qe(int fwd, t_env *e)
{
	if (e->fid == 4)
		tree_change_len(e, fwd);
	if (e->fid == 5)
		sponge_change_depth(e, fwd);
	return (0);
}
