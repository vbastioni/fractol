/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:05:49 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/18 13:44:19 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"

void		ft_putchar_fd(int c, int fd)
{
	unsigned char	cc[4];
	int				bcnt;

	bcnt = ft_countbits(c);
	if (bcnt < 12)
	{
		cc[0] = 0xC0 | ((c & 0x7C0) >> 6);
		cc[1] = 0x80 | (c & 0x3F);
		write(fd, (bcnt < 8 ? (char *)&c : (char *)cc), ((bcnt < 8) ? 1 : 2));
	}
	else if (bcnt > 11 && bcnt < 22)
	{
		cc[0] = bcnt < 17 ? (0xE0 | ((c & 0xF000) >> 12)) :
			(0xF0 | ((c & 0x1C0000) >> 18));
		cc[1] = bcnt < 17 ? (0x80 | ((c & 0xFC0) >> 6)) :
			(0x80 | ((c & 0x3F000) >> 12));
		cc[2] = bcnt < 17 ? (0x80 | (c & 0x3F)) :
			(0x80 | ((c & 0xFC0) >> 6));
		cc[3] = 0x80 | (c & 0x3F);
		write(fd, cc, bcnt < 17 ? 3 : 4);
	}
}
