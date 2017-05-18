/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 12:10:47 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/12 19:55:17 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		ft_bzero(void *s, size_t n)
{
	char	*ss;
	size_t	i;

	if (n == 0)
		return ;
	i = 0;
	ss = (char *)s;
	while (i < n)
	{
		*(ss + i) = 0;
		i++;
	}
}
