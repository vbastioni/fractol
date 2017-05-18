/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 14:03:04 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/13 19:39:15 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*ret;
	size_t	i;

	if (!(ret = (void *)malloc(size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		*(((char*)ret) + i) = 0;
		i++;
	}
	return (ret);
}
