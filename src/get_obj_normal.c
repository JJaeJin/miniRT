/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:23:34 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/03/15 13:10:21 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "vector.h"

t_vector	get_plane_normal(t_vector light, t_camera *cam, \
							t_obj_plane *pl, t_point p)
{
	t_vector	res;
	double		inner_cam_point;
	double		inner_light_point;

	inner_cam_point = v_inner_product(cam->way, p);
	inner_light_point = v_inner_product(light, p);
	res.x = cam->way.x;
	res.y = cam->way.y;
	res.z = cam->way.z;
	if ((inner_cam_point > 0 && inner_light_point > 0)
		|| (inner_cam_point < 0 && inner_light_point < 0))
	{
		res.x *= (-1);
		res.y *= (-1);
		res.z *= (-1);
	}
	return (res);
}

t_vector	get_sphere_normal(t_vector light, t_obj_sphere *sp, t_point p)
{
	t_vector	normal;

	normal = p_get_vector(sp->center, p);
	v_normalize(&normal);
	return (normal);
}

t_vector	get_cylinder_normal(t_vector light, t_obj_cylinder *cy, t_point p)
{
	t_vector	v_center_to_point;
	t_vector	p_center_of_point_pl;
	t_vector	res_normal;
	double		size_of_normal;
	double		distance;

	v_center_to_point = p_get_vector(cy->normal, p);
	size_of_normal = v_inner_product(v_center_to_point, cy->normal);
	p_center_of_point_pl.x = cy->loc.x + cy->normal.x * size_of_normal;
	p_center_of_point_pl.y = cy->loc.y + cy->normal.y * size_of_normal;
	p_center_of_point_pl.z = cy->loc.z + cy->normal.z * size_of_normal;
	res_normal = p_get_vector(p_center_of_point_pl, p);
	v_normalize(&res_normal);
	return (res_normal);
}