/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:44:55 by jaejilee          #+#    #+#             */
/*   Updated: 2023/11/11 11:14:04 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# elif BUFFER_SIZE <= 0
#  error "error"
# endif

# define SUCCESS 1
# define ERROR 0

char	*get_next_line(int fd);

typedef struct s_glst
{
	int				fd;
	char			*content;
	size_t			len;
	struct s_glst	*next;
}	t_glst;

t_glst	*go_to_node(int fd, t_glst **first);
char	*get_res(t_glst *n);
int		add_buffer(t_glst *n, size_t add);
int		find_nl(t_glst *n);

int		read_buff(t_glst *n);
char	*make_res(t_glst *n);
t_glst	*set_nn(t_glst **lst, t_glst *new, int fd, ssize_t rd_size);
int		trim_con(t_glst *n, int i, size_t res_len);
void	*free_error(void *v);

#endif