/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:34:25 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/13 17:54:28 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned short	i;
	unsigned short	j;
	size_t			olen;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (*(big + i) && len)
	{
		if (*(big + i) == *little)
		{
			olen = len;
			j = 0;
			while (*(big + i + j) == *(little + j) && olen-- &&
					*(big + i + j) && *(little + j))
				j++;
			if (*(little + j) == '\0' && len)
				return ((char *)(big + i));
		}
		i++;
		len--;
	}
	return (NULL);
}
