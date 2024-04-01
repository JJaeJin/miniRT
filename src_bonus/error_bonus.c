/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:56:52 by jaejilee          #+#    #+#             */
/*   Updated: 2024/04/01 13:57:47 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "argument_bonus.h"

static void	free_obj(t_obj *objs);

int	return_error(char *s)
{
	ft_putstr_fd("Error\nminiRT: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	return (FAILURE);
}

void	free_all_info(t_info *info)
{
	t_light	*temp_light;

	free(info->camera);
	free(info->amb);
	while (info->lights != NULL)
	{
		temp_light = info->lights->next;
		free(info->lights);
		info->lights = temp_light;
	}
	free_obj(info->objs);
	free(info->objs);
}

static void	free_obj(t_obj *objs)
{
	t_obj_cylinder	*temp_cy;
	t_obj_plane		*temp_pl;
	t_obj_sphere	*temp_sp;

	while (objs->cy != NULL)
	{
		temp_cy = objs->cy->next;
		free(objs->cy);
		objs->cy = temp_cy;
	}
	while (objs->pl != NULL)
	{
		temp_pl = objs->pl->next;
		free(objs->pl);
		objs->pl = temp_pl;
	}
	while (objs->sp != NULL)
	{
		temp_sp = objs->sp->next;
		free(objs->sp);
		objs->sp = temp_sp;
	}
}

int	free_double_char_pointer_rt_int(char **ptr, int rt_value)
{
	int	idx;

	idx = 0;
	while (ptr[idx] != NULL)
	{
		free(ptr[idx]);
		idx++;
	}
	free(ptr);
	return (rt_value);
}
