/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 09:12:59 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/18 09:13:39 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_itoabase(int n, char *base)
{
	int		len;
	long	nb;
	int		blen;
	char	*ret;
	int		is_neg;

	if (!base || !ft_valid_base(base, &blen))
		return (NULL);
	is_neg = n < 0;
	len = 1;
	nb = is_neg ? -((long)n) : (long)n;
	while ((nb /= blen) > 0)
		len++;
	ret = ft_strnew(len + is_neg);
	nb = is_neg ? -((long)n) : (long)n;
	while (--len > -1)
	{
		ret[len + is_neg] = base[nb % blen];
		nb /= blen;
	}
	ret[0] = is_neg ? '-' : ret[0];
	return (ret);
}
