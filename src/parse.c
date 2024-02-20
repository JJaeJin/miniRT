/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:45:37 by jaejilee          #+#    #+#             */
/*   Updated: 2024/02/20 11:24:26 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "argument.h"
#include "get_next_line.h"
#include "fcntl.h"

static int	is_rt_file(char *file);
static int	read_info(t_info *info, char *buffer);
static int	parse_finished(t_info *info);

int	parse_all(t_info *info, char *file)
{
	char	*buffer;
	int		fd;

	if (is_rt_file(file) == FALSE)
		return (FAILURE);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (FAILURE);
	while (1)
	{
		buffer = get_next_line(fd);
		if (buffer == 0)
			break ;
		if (read_info(info, buffer) == FAILURE)
		{
			free(buffer);
			close(fd);
			return (FAILURE);
		}
		free(buffer);
	}
	if (parse_finished(info) == FALSE)
		return (FAILURE);
	return (SUCCESS);
}

static int	is_rt_file(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len <= 3 || ft_strncmp(file + (len - 3), ".rt", 4) != 0)
		return (FALSE);
	return (TRUE);
}

static int	read_info(t_info *info, char *buffer)
{
	char	**all_info;

	all_info = ft_split(buffer, ' ');
	if (all_info == 0)
		return (FAILURE);
	if (all_info[0] == NULL)
		return (0);
	else if (ft_strncmp(all_info[0], "sp", 3) == 0)
		return (read_sp());
	else if (ft_strncmp(all_info[0], "pl", 3) == 0)
		return (read_pl());
	else if (ft_strncmp(all_info[0], "cy", 3) == 0)
		return (read_cy());
	else if (ft_strncmp(all_info[0], "A", 2) == 0)
		return (read_amb());
	else if (ft_strncmp(all_info[0], "C", 2) == 0)
		return (read_cam());
	else if (ft_strncmp(all_info[0], "L", 2) == 0)
		return (read_light());
	else
		return (FAILURE);
}

static int	parse_finished(t_info *info)
{
	if (info->amb == 0
		|| info->camera == 0
		|| info->lights == 0)
		return (FALSE);
	return (TRUE);
}

int	fail_free(void *p)
{
	free(p);
	return (FAILURE);
}
