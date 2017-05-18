/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 11:53:30 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/14 12:13:34 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstmerge(t_list **lhs, t_list *rhs)
{
	t_list	*head;

	if (!lhs || !rhs)
		return ;
	if (!*lhs)
		*lhs = rhs;
	else
	{
		head = *lhs;
		while (head->next)
			head = head->next;
		head->next = rhs;
	}
}
