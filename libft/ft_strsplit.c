/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 17:54:02 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/13 19:53:28 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		flush(char **tab, int cnt)
{
	while (cnt > 0)
	{
		free(*tab);
		tab--;
		cnt--;
	}
	return (0);
}

static int		copy(char **tab, char const *beg, char const *end)
{
	char		*tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * (end - beg + 1))))
		return (0);
	*tab = tmp;
	while (beg != end)
	{
		*tmp = *beg;
		beg++;
		tmp++;
	}
	*tmp = '\0';
	return (1);
}

static int		split(char **tab, char const *s, int cnt, char c)
{
	int			i;
	char const	*beg;

	beg = NULL;
	i = 0;
	cnt = 0;
	while (*(s + i))
	{
		if ((*(s + i) != c) && !beg)
			beg = s + i;
		else if ((*(s + i) == c) && beg)
		{
			if (!copy(tab, beg, s + i))
				return (flush(tab - 1, cnt));
			else
				cnt++;
			tab++;
			beg = 0;
		}
		i++;
	}
	if (beg)
		copy(tab++, beg, s + i);
	*tab = 0;
	return (1);
}

static int		count_words(char const *s, char c)
{
	int			i;
	int			flags;
	int			cnt;

	i = 0;
	flags = 0;
	cnt = 0;
	while (*(s + i))
	{
		if ((*(s + i) != c) && (!(flags & 1)))
		{
			flags |= 1;
			cnt++;
		}
		else if ((*(s + i) == c) && (flags & 1))
			flags ^= 1;
		i++;
	}
	return (cnt);
}

char			**ft_strsplit(char const *s, char c)
{
	int			cnt;
	char		**ret;

	cnt = 0;
	if (!s)
		return (NULL);
	cnt = count_words(s, c);
	if (!(ret = (char **)malloc(sizeof(char *) * (cnt + 1))))
		return (NULL);
	*(ret + cnt) = 0;
	if (split(ret, s, cnt, c))
		return (ret);
	return (NULL);
}
