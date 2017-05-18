/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:02:57 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/13 17:55:18 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int			ft_strnequ(char const *s1, char const *s2, size_t n)
{
	unsigned int	i;

	if (!s1 || !s2)
		return (0);
	if (!n)
		return (1);
	i = 0;
	while (*(s1 + i) && *(s2 + i) && n > 0)
	{
		if (*(s1 + i) != *(s2 + i))
			return (0);
		i++;
		n--;
	}
	return (*(s1 + (n ? i : (i - 1))) == *(s2 + (n ? i : (i - 1))));
}
