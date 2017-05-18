/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 13:18:26 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/13 18:48:56 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*cs;
	unsigned char		cc;

	cs = (const unsigned char *)s;
	cc = (unsigned char)c;
	if (!n)
		return (NULL);
	while (1)
	{
		if (*(cs++) == cc)
			return ((void *)(cs - 1));
		if (--n == 0)
			break ;
	}
	return (NULL);
}
