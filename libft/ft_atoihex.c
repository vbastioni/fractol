/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoihex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 14:57:37 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/17 13:34:19 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int		ft_atoihex(const char *nbr)
{
	int				i;
	unsigned int	ret;

	if (!nbr)
		return (0);
	while (ft_isspace(*nbr))
		nbr++;
	if (ft_strncmp(nbr, "0x", 2) == 0)
		nbr += 2;
	ret = 0;
	i = 0;
	while (*(nbr + i))
	{
		if (*(nbr + i) >= '0' && *(nbr + i) <= '9')
			ret = (ret * 16 + (*(nbr + i) - '0'));
		else if (*(nbr + i) >= 'A' && *(nbr + i) <= 'F')
			ret = (ret * 16 + (*(nbr + i) - 'A' + 10));
		else if (*(nbr + i) >= 'a' && *(nbr + i) <= 'f')
			ret = (ret * 16 + (*(nbr + i) - 'a' + 10));
		else
			break ;
		i++;
	}
	return (ret);
}
