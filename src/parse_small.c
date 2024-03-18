/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_small.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:00:52 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/18 10:10:41 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "argument.h"
#include "error.h"
#include "vector.h"

int	read_sp(t_obj *obj, char **all_info)
{
	t_obj_sphere	*res;

	res = (t_obj_sphere *)ft_calloc(1, sizeof(t_obj_sphere));
	if (all_info[1] == NULL \
		|| is_vector(all_info[1], &(res->center)) == FALSE)
		return (fail_free(res));
	if (all_info[2] == NULL \
		|| is_unsigned_double(all_info[2], &(res->diameter)) == FALSE)
		return (fail_free(res));
	if (all_info[3] == NULL \
		|| is_rgb(all_info[3], &(res->color)) == FALSE)
		return (fail_free(res));
	if (all_info[4] != NULL)
		return (fail_free(res));
	res->next = obj->sp;
	obj->sp = res;
	return (SUCCESS);
}

int	read_pl(t_obj *obj, char **all_info)
{
	t_obj_plane	*res;

	res = (t_obj_plane *)ft_calloc(1, sizeof(t_obj_plane));
	if (all_info[1] == NULL \
		|| is_vector(all_info[1], &(res->loc)) == FALSE)
		return (fail_free(res));
	if (all_info[2] == NULL \
		|| is_vector(all_info[2], &(res->normal)) == FALSE)
		return (fail_free(res));
	if (all_info[3] == NULL \
		|| is_rgb(all_info[3], &(res->color)) == FALSE)
		return (fail_free(res));
	if (all_info[4] != NULL)
		return (fail_free(res));
	res->next = obj->pl;
	obj->pl = res;
	v_normalize(&obj->pl->normal);
	return (SUCCESS);
}

int	read_cy(t_obj *obj, char **all_info)
{
	t_obj_cylinder	*res;

	res = ft_calloc(1, sizeof(t_obj_cylinder));
	if (all_info[1] == NULL \
		|| is_vector(all_info[1], &(res->loc)) == FALSE)
		return (fail_free(res));
	if (all_info[2] == NULL \
		|| is_vector(all_info[2], &(res->normal)) == FALSE)
		return (fail_free(res));
	if (all_info[3] == NULL \
		|| is_unsigned_double(all_info[3], &(res->diameter)) == FALSE)
		return (fail_free(res));
	if (all_info[4] == NULL \
		|| is_unsigned_double(all_info[4], &(res->height)) == FALSE)
		return (fail_free(res));
	if (all_info[5] == NULL \
		|| is_rgb(all_info[5], &(res->color)) == FALSE)
		return (fail_free(res));
	if (all_info[6] != NULL)
		return (fail_free(res));
	res->next = obj->cy;
	obj->cy = res;
	v_normalize(&obj->cy->normal);
	return (SUCCESS);
}

int	read_co(t_obj *obj, char **all_info)
{
	t_obj_cone	*res;

	res = ft_calloc(1, sizeof(t_obj_cone));
	if (all_info[1] == NULL \
		|| is_vector(all_info[1], &(res->loc)) == FALSE)
		return (fail_free(res));
	if (all_info[2] == NULL \
		|| is_vector(all_info[2], &(res->normal)) == FALSE)
		return (fail_free(res));
	if (all_info[3] == NULL \
		|| is_unsigned_double(all_info[3], &(res->diameter)) == FALSE)
		return (fail_free(res));
	if (all_info[4] == NULL \
		|| is_unsigned_double(all_info[4], &(res->height)) == FALSE)
		return (fail_free(res));
	if (all_info[5] == NULL \
		|| is_rgb(all_info[5], &(res->color)) == FALSE)
		return (fail_free(res));
	if (all_info[6] != NULL)
		return (fail_free(res));
	res->next = obj->co;
	obj->co = res;
	v_normalize(&obj->co->normal);
	return (SUCCESS);
}
