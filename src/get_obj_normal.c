/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:23:34 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/03/15 19:56:40 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "vector.h"
#include <stdio.h>

t_vector	get_plane_normal(t_camera *cam, t_obj_plane *pl)
{
	t_vector	res;
	double		inner_cam_n;

	inner_cam_n = v_inner_product(cam->way, pl->normal);
	res.x = pl->normal.x;
	res.y = pl->normal.y;
	res.z = pl->normal.z;
	if (inner_cam_n > 0)
	{
		res.x *= (-1);
		res.y *= (-1);
		res.z *= (-1);
	}
	return (res);
}

t_vector	get_sphere_normal(t_obj_sphere *sp, t_point p)
{
	t_vector	normal;

	normal = p_get_vector(sp->center, p);
	v_normalize(&normal);
	return (normal);
}

t_vector	get_cylinder_normal(t_obj_cylinder *cy, t_point p)
{
	t_vector	v_center_to_point;
	t_vector	p_center_of_point_pl;
	t_vector	res_normal;
	double		size_of_normal;

	v_center_to_point = p_get_vector(cy->loc, p);
	size_of_normal = v_inner_product(v_center_to_point, cy->normal);
	p_center_of_point_pl.x = cy->loc.x + cy->normal.x * size_of_normal;
	p_center_of_point_pl.y = cy->loc.y + cy->normal.y * size_of_normal;
	p_center_of_point_pl.z = cy->loc.z + cy->normal.z * size_of_normal;
	res_normal = p_get_vector(p_center_of_point_pl, p);
	v_normalize(&res_normal);
	// printf("p in center = (%f, %f, %f)\n\n", p_center_of_point_pl.x, p_center_of_point_pl.y, p_center_of_point_pl.z);
	return (res_normal);
}

t_vector	get_cylinder_normal_bottom(t_camera *cam, t_obj_cylinder *cy)
{
	t_vector	res;
	double		inner_cam_n;

	inner_cam_n = v_inner_product(cam->way, cy->normal);
	res.x = cy->normal.x;
	res.y = cy->normal.y;
	res.z = cy->normal.z;
	if (inner_cam_n > 0)
	{
		res.x *= (-1);
		res.y *= (-1);
		res.z *= (-1);
	}
	return (res);
}
