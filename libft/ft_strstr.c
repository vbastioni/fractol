/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:26:43 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/13 17:47:44 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char		*ft_strstr(const char *big, const char *little)
{
	unsigned short	i;
	unsigned short	j;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (*(big + i))
	{
		if (*(big + i) == *little)
		{
			j = 0;
			while (*(big + i + j) == *(little + j) &&
					*(big + i + j) && *(little + j))
				j++;
			if (*(little + j) == '\0')
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
