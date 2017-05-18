/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoinbase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 15:00:02 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/15 15:00:28 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_atoinbase(const char *nbr)
{
	int			len;

	if (!nbr)
		return (0);
	len = ft_strlen(nbr);
	while (ft_isspace(*nbr))
		nbr++;
	if (len >= 2 && nbr[0] == '0' && nbr[1] == 'x')
		return (ft_atoibase(nbr + 2, "0123456789ABCDEF"));
	else if (len >= 1 && nbr[0] == '0')
		return (ft_atoibase(nbr + 0, "01234567"));
	else
		return (ft_atoibase(nbr, "0123456789"));
}
