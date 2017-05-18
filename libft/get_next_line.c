/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 14:55:37 by vbastion          #+#    #+#             */
/*   Updated: 2017/05/17 12:57:31 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "get_next_line.h"

static t_list		*fds_fd(const int fd, t_list **fds)
{
	t_list			*head;
	t_list			*new;

	if (!(fds))
		return (NULL);
	head = *fds;
	while (head)
	{
		if (head->content && head->content_size == (size_t)fd)
			return (head);
		head = head->next;
	}
	if (!(new = ft_lstnew(NULL, 0)))
		return (NULL);
	new->content = ft_strnew(0);
	new->content_size = fd;
	ft_lstadd(fds, new);
	return (*fds);
}

void				add_in_rem(char *buf, int sz, t_list *t)
{
	char			*tmp_a;
	char			*tmp_b;

	tmp_a = ft_strsub(buf, 0, (size_t)sz);
	tmp_b = ft_strjoin(t->content, tmp_a);
	free(tmp_a);
	free(t->content);
	t->content = tmp_b;
}

int					handle_rem(char *sub, t_list *t, char **line)
{
	size_t			delta;
	char			*tmp;

	delta = sub ? (sub - (char *)t->content) : ft_strlen(t->content);
	*line = ft_strsub(t->content, 0, delta);
	tmp = ft_strsub(t->content, delta + 1, ft_strlen(t->content) - delta + 1);
	free(t->content);
	t->content = tmp;
	return (1);
}

void				handle_data(char *str[0], int sz, t_list *t, char **line)
{
	size_t			delta;
	char			*tmp;

	delta = str[0] ? str[0] - str[1] : sz;
	tmp = ft_strsub(str[1], 0, delta);
	*line = ft_strjoin(t->content, tmp);
	free(tmp);
	free(t->content);
	t->content = ((delta + 1) >= (size_t)sz) ? ft_strnew(0) :
		ft_strsub(str[1], delta + 1, sz - delta - 1);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*fds = 0;
	t_list			*t;
	char			buf[BUFF_SIZE];
	int				b_sz;
	char			*tmp[2];

	if (fd < 0 || !line)
		return (-1);
	tmp[0] = 0;
	if (!(t = fds_fd(fd, &fds)))
		return (-1);
	if (ft_strlen(t->content) && (tmp[0] = ft_strstr(t->content, "\n")))
		return (handle_rem(tmp[0], t, line));
	while ((b_sz = read(fd, buf, BUFF_SIZE)) > 0 &&
			!(tmp[0] = ft_memchr(buf, '\n', b_sz)))
		add_in_rem(buf, b_sz, t);
	if (b_sz == -1)
		return (-1);
	if (b_sz < 1 && !(ft_strlen(t->content) > 0))
		return (0);
	tmp[1] = buf;
	handle_data(tmp, b_sz, t, line);
	return (ft_strlen(*line) > 0);
}
