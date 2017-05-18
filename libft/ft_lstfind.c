/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 10:56:46 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/14 11:47:31 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <string.h>

t_list		*ft_lstfind(t_list *lst, const void *content, size_t size)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (!ft_memcmp(lst->content, content, (size <= lst->content_size ?
						size : lst->content_size)))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
