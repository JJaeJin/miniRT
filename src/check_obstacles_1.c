/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_obstacles_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:37:36 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/03/31 11:27:52 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "vector.h"
#include <math.h>

static double	get_pl_res(t_obj_plane *pl, t_point p);

int	check_obstacles(t_point l, t_point p, t_info info, void *obj)
{
	if (check_obs_sphere(l, p, info.objs->sp, obj) == OBS_EXIST)
		return (OBS_EXIST);
	else if (check_obs_plane(l, p, info.objs->pl, obj) == OBS_EXIST)
		return (OBS_EXIST);
	else if (check_obs_cylinder(l, p, info.objs->cy, obj) == OBS_EXIST)
		return (OBS_EXIST);
	else if (check_obs_cone(l, p, info.objs->co, obj) == OBS_EXIST)
		return (OBS_EXIST);
	return (OBS_NOT_EXIST);
}

int	check_obs_sphere(t_point l, t_point p, t_obj_sphere *sp, void *obj)
{
	t_obj_sphere	*temp_sp;
	double			sp_to_ray;
	double			temp;
	t_vector		p_to_l;
	t_vector		p_to_sp;

	temp_sp = sp;
	p_to_l = p_get_vector(p, l);
	v_normalize(&p_to_l);
	while (temp_sp != NULL)
	{
		if ((void *)temp_sp != obj)
		{
			p_to_sp = p_get_vector(p, temp_sp->center);
			temp = v_inner_product(p_to_l, p_to_sp);
			sp_to_ray = sqrt(fabs(pow(v_size(p_to_sp), 2) - \
						pow(temp, 2)));
			if (is_in_sp(p, temp_sp) * is_in_sp(l, temp_sp) == -1 || \
				(temp > 0 && temp < v_size(p_to_l) && \
				sp_to_ray <= temp_sp->diameter / 2))
				return (OBS_EXIST);
		}
		temp_sp = temp_sp->next;
	}
	return (OBS_NOT_EXIST);
}

int	check_obs_plane(t_point l, t_point p, t_obj_plane *pl, void *obj)
{
	t_obj_plane	*temp_pl;
	t_vector	p_to_l;

	temp_pl = pl;
	p_to_l = p_get_vector(p, l);
	v_normalize(&p_to_l);
	while (temp_pl != NULL)
	{
		if ((void *)temp_pl != obj && \
			get_pl_res(temp_pl, p) * get_pl_res(temp_pl, l) < 0)
			return (OBS_EXIST);
		temp_pl = temp_pl->next;
	}	
	return (OBS_NOT_EXIST);
}

static double	get_pl_res(t_obj_plane *pl, t_point p)
{
	double	res;

	res = pl->normal.x * (p.x - pl->loc.x) + \
			pl->normal.y * (p.y - pl->loc.y) + \
			pl->normal.z * (p.z - pl->loc.z);
	return (res);
}
