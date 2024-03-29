/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:46:07 by jaejilee          #+#    #+#             */
/*   Updated: 2024/02/20 14:28:48 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_glst	*set_nn(t_glst **lst, t_glst *new, int fd, ssize_t rd_size)
{
	new->next = *lst;
	new->fd = fd;
	new->len = rd_size;
	*lst = new;
	return (new);
}

int	read_buff(t_glst *n)
{
	ssize_t	rd_size;

	rd_size = read(n->fd, n->content + n->len, BUFFER_SIZE);
	if (rd_size == -1 || (rd_size == 0 && n->len == 0))
		return (FALSE);
	n->len += rd_size;
	return (TRUE);
}

char	*make_res(t_glst *n)
{
	char	*res;
	int		i;
	size_t	res_len;

	if (n->len == 0)
		return (FALSE);
	if (find_nl(n) != -1)
		res_len = find_nl(n) + 1;
	else
		res_len = n->len;
	res = (char *)malloc(res_len + 1);
	if (res == 0)
		return (FALSE);
	i = -1;
	while (++i < (int)res_len)
		res[i] = n->content[i];
	res[res_len] = 0;
	if (n->len != res_len)
	{
		if (trim_con(n, i, res_len) == 0)
			return (free_error(res));
	}
	n->len -= res_len;
	return (res);
}

int	trim_con(t_glst *n, int i, size_t res_len)
{
	char	*tmp_con;

	tmp_con = (char *)malloc(n->len - res_len);
	if (tmp_con == 0)
		return (FALSE);
	while ((size_t)i < n->len)
	{
		tmp_con[i - res_len] = n->content[i];
		i++;
	}
	free(n->content);
	n->content = tmp_con;
	return (TRUE);
}

void	*free_error(void *v)
{
	free(v);
	return (FALSE);
}
