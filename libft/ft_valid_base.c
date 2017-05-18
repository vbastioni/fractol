/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 09:10:47 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/18 09:11:32 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_valid_base(const char *base, int *blen)
{
	int	i;

	(*blen) = 0;
	while (*(base + (*blen)))
	{
		if (*(base + (*blen)) == 0x2b || *(base + (*blen)) == 0x2d)
			return (0);
		i = (*blen);
		while (--i > -1)
		{
			if (base[i] == base[(*blen)])
				return (0);
		}
		(*blen)++;
	}
	return ((*blen) > 1);
}
