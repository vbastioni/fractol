/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 19:51:35 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/14 11:51:51 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"

void		ft_putstr(char const *s)
{
	unsigned short	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write(1, s, len);
}
