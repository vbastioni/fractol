/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:58:40 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/12 20:38:05 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*curr;
	t_list	*tmp;

	curr = *alst;
	while (curr)
	{
		(*del)(curr->content, curr->content_size);
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	*alst = NULL;
}
