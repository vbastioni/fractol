/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 10:38:18 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/14 11:10:02 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "libft.h"

t_list	*ft_lstat(t_list *lst, int index)
{
	if (!lst || index < 0)
		return (NULL);
	while (lst && index >= 0)
	{
		if (index == 0)
			return (lst);
		index--;
		lst = lst->next;
	}
	return (NULL);
}
