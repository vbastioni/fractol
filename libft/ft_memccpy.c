/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 12:13:53 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/13 17:54:52 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*cdst;
	unsigned char const	*csrc;
	size_t				i;
	unsigned char		cc;

	if (!n)
		return (NULL);
	i = 0;
	cc = (unsigned char)c;
	cdst = (unsigned char *)dst;
	csrc = (unsigned char const *)src;
	while (n > 0)
	{
		*(cdst + i) = *(csrc + i);
		if (*(csrc + i) == cc)
			return (cdst + i + 1);
		i++;
		n--;
	}
	return (NULL);
}
