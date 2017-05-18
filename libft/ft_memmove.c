/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 12:56:57 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/13 18:49:59 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	int					fwd;
	unsigned char const	*csrc;
	unsigned char		*cdst;

	if (len == 0)
		return (dst);
	cdst = (unsigned char *)dst;
	csrc = (unsigned char const *)src;
	fwd = ((unsigned long)dst < (unsigned long)src);
	if (fwd)
		while (len--)
			*(cdst++) = *(csrc++);
	else
	{
		while (1)
		{
			--len;
			*(cdst + len) = *(csrc + len);
			if (len == 0)
				break ;
		}
	}
	return (dst);
}
