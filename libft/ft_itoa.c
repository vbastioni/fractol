/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 19:29:32 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/12 17:19:55 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char		*ft_itoa(int n)
{
	long	nb;
	int		is_signed;
	char	*ret;
	int		len;

	is_signed = (n < 0) ? 1 : 0;
	nb = is_signed ? -((long)n) : ((long)n);
	len = 1 + is_signed;
	while (nb /= 10)
		len++;
	if (!(ret = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ret[len] = '\0';
	nb = is_signed ? -((long)n) : ((long)n);
	while (--len >= 0)
	{
		ret[len] = '0' + nb % 10;
		nb /= 10;
	}
	ret[0] = is_signed ? '-' : ret[0];
	return (ret);
}
