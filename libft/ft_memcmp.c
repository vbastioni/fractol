/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:18:41 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/13 18:49:37 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int			ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*cs1;
	const unsigned char	*cs2;

	cs1 = (const unsigned char *)s1;
	cs2 = (const unsigned char *)s2;
	if (n == 0)
		return (n);
	while (1)
	{
		if (*cs1 != *cs2 || --n == 0)
			break ;
		cs1++;
		cs2++;
	}
	return (*cs1 - *cs2);
}
