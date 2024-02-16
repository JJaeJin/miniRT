/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:34:28 by jaejilee          #+#    #+#             */
/*   Updated: 2023/11/20 16:18:57 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_glst	*first;
	t_glst			*now;
	char			*res;
	t_glst			*tmp_nod;

	now = go_to_node(fd, &first);
	if (now == 0)
		return (ERROR);
	res = get_res(now);
	if (res == 0)
	{
		if (now == first)
		{
			first = first->next;
			free(now->content);
			return (free_error(now));
		}
		tmp_nod = first;
		while (tmp_nod->next != now)
			tmp_nod = tmp_nod->next;
		tmp_nod->next = now->next;
		free(now->content);
		return (free_error(now));
	}
	return (res);
}

t_glst	*go_to_node(int fd, t_glst **first)
{
	t_glst	*res;
	t_glst	*n_n;
	ssize_t	rd_size;

	res = *first;
	if (res != 0)
		while (res->fd != fd && res->next != 0)
		res = res->next;
	if (res == 0 || res->fd != fd)
	{
		n_n = (t_glst *)malloc(sizeof(t_glst));
		if (n_n == 0)
			return (ERROR);
		n_n->content = (char *)malloc(BUFFER_SIZE);
		rd_size = read(fd, n_n->content, BUFFER_SIZE);
		if (n_n->content == 0 || rd_size <= 0)
		{
			free(n_n->content);
			return (free_error(n_n));
		}
		return (set_nn(first, n_n, fd, rd_size));
	}
	return (res);
}

char	*get_res(t_glst *n)
{
	size_t	i;
	size_t	d;
	size_t	add;

	if (read(n->fd, 0, 0) == -1)
		return (ERROR);
	add = n->len;
	i = 0;
	d = 1;
	while (find_nl(n) == -1 && n->len - add == (size_t)i * BUFFER_SIZE)
	{
		if (i == d || i == 0)
		{
			if (i != 0)
				d *= 2;
			if (add_buffer(n, d * BUFFER_SIZE) == 0)
				return (ERROR);
		}
		if (read_buff(n) == 0)
			return (ERROR);
		i++;
	}
	return (make_res(n));
}

int	find_nl(t_glst *n)
{
	size_t	i;

	i = 0;
	while (i < n->len)
	{
		if (n->content[i] == '\n')
			return (i);
		++i;
	}
	return (-1);
}

int	add_buffer(t_glst *n, size_t add)
{
	char	*tmp_con;
	size_t	i;

	i = 0;
	tmp_con = (char *)malloc(n->len + add);
	if (tmp_con == 0)
		return (ERROR);
	while (i < n->len)
	{
		tmp_con[i] = n->content[i];
		i++;
	}
	free(n->content);
	n->content = tmp_con;
	return (SUCCESS);
}
