/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:07:18 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/12 20:56:33 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static void	*flush(t_list *head)
{
	t_list	*curr;

	while (head)
	{
		curr = head;
		head = head->next;
		free(curr);
	}
	return (NULL);
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*head;
	t_list	*prev;
	t_list	*curr;

	if (!lst)
		return (NULL);
	prev = NULL;
	while (lst)
	{
		if (!(curr = (*f)(lst)))
			return (flush(prev));
		if (prev)
			prev->next = curr;
		else
			head = curr;
		prev = curr;
		lst = lst->next;
	}
	return (head);
}
