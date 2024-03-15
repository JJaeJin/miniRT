/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_obstacles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:37:36 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/03/14 20:19:25 by jaejilee         ###   ########.fr       */
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
			v_normalize(&p_to_sp);
			temp = v_inner_product(p_to_l, p_to_sp);
			sp_to_ray = sqrt(fabs(pow(v_size(p_to_sp), 2) - \
						pow(temp, 2)));
			if (temp > 0 && temp < v_size(p_to_l) && \
				sp_to_ray <= temp_sp->diameter / 2)
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
			pl->normal.z * (p.x - pl->loc.z);
	return (res);
}

int	check_obs_cylinder(t_point l, t_point p, t_obj_cylinder *cy, void *obj)
{
	t_obj_cylinder	*temp_cy;
	t_vector		p_to_l;
	t_vector		l_to_cy;
	double			d_between_lines;
	double			temp;

	temp_cy = cy;
	p_to_l = p_get_vector(p, l);
	v_normalize(&p_to_l);
	while (temp_cy != NULL)
	{
		l_to_cy = p_get_vector(l, temp_cy->loc);
		d_between_lines = get_d_between_lines(p_to_l, temp_cy);
		temp = pow(v_inner_product(p_to_l, l_to_cy), 2) + \
				pow(d_between_lines, 2);
		temp = sqrt(fabs(pow(v_size(l_to_cy), 2) - temp));
		if (d_between_lines < temp_cy->diameter / 2 && \
			temp < temp_cy->height / 2)
			return (OBS_EXIST);
	}
	return (OBS_NOT_EXIST);
}
