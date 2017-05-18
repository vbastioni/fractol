/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:53:51 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/12 21:13:53 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	tmp;

	i = 0;
	j = 0;
	while (dst[i] && i < size)
		i++;
	tmp = i;
	while (size && src[j] && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (tmp < size)
		dst[i] = '\0';
	return (tmp + ft_strlen(src));
}
