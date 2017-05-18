/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:50:14 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/13 19:56:37 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

static void	cpy(char *buf, char const *beg, char const *end)
{
	int			i;

	i = 0;
	while ((beg + i) != end)
	{
		*(buf + i) = *(beg + i);
		i++;
	}
}

char		*ft_strtrim(char const *s)
{
	char const	*first;
	char const	*last;
	char		*ret;

	if (!s)
		return (NULL);
	while (is_whitespace(*s))
		s++;
	first = s;
	last = s;
	while (*s)
	{
		if (!is_whitespace(*s))
			last = s;
		s++;
	}
	last++;
	if (!(ret = (char *)malloc(sizeof(char) * (last - first + 1))))
		return (NULL);
	if ((last - first) > 0)
		cpy(ret, first, last);
	*(ret + (last - first)) = '\0';
	return (ret);
}
