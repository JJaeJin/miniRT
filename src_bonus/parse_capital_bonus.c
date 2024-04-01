/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_capital_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:32:02 by jaejilee          #+#    #+#             */
/*   Updated: 2024/04/01 13:57:47 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "argument_bonus.h"
#include "vector_bonus.h"

int	read_cam(t_info *info, char **all_info)
{
	t_camera	*res;

	if (info->camera != NULL)
		return (FAILURE);
	res = (t_camera *)ft_calloc(1, sizeof(t_camera));
	if (all_info[1] == NULL \
		|| is_vector(all_info[1], &(res->loc)) == FALSE)
		return (fail_free(res, all_info));
	if (all_info[2] == NULL \
		|| is_vector(all_info[2], &(res->way)) == FALSE \
		|| (res->way.x == 0 && res->way.y == 0 && res->way.z == 0))
		return (fail_free(res, all_info));
	if (all_info[3] == NULL \
		|| is_unsigned_double(all_info[3], &(res->fov)) == FALSE \
		|| res->fov >= 180)
		return (fail_free(res, all_info));
	if (all_info[4] != NULL)
		return (fail_free(res, all_info));
	info->camera = res;
	v_normalize(&info->camera->way);
	return (free_double_char_pointer_rt_int(all_info, SUCCESS));
}

int	read_light(t_info *info, char **all_info)
{
	t_light	*res;

	res = (t_light *)ft_calloc(1, sizeof(t_light));
	if (all_info[1] == NULL \
		|| is_vector(all_info[1], &(res->loc)) == FALSE)
		return (fail_free(res, all_info));
	if (all_info[2] == NULL \
		|| is_unsigned_double(all_info[2], &(res->ratio)) == FALSE)
		return (fail_free(res, all_info));
	if (all_info[3] == NULL \
		|| is_rgb(all_info[3], &(res->color)) == FALSE)
		return (fail_free(res, all_info));
	if (all_info[4] != NULL)
		return (fail_free(res, all_info));
	res->next = info->lights;
	info->lights = res;
	return (free_double_char_pointer_rt_int(all_info, SUCCESS));
}

int	read_amb(t_info *info, char **all_info)
{
	t_ambient_lightning	*res;

	if (info->amb != NULL)
		return (FAILURE);
	res = (t_ambient_lightning *)ft_calloc(1, sizeof(t_ambient_lightning));
	if (all_info[1] == NULL \
		|| is_unsigned_double(all_info[1], &(res->ratio)) == FALSE)
		return (fail_free(res, all_info));
	if (all_info[2] == NULL \
		|| is_rgb(all_info[2], &(res->color)) == FALSE)
		return (fail_free(res, all_info));
	if (all_info[3] != NULL)
		return (fail_free(res, all_info));
	info->amb = res;
	return (free_double_char_pointer_rt_int(all_info, SUCCESS));
}
