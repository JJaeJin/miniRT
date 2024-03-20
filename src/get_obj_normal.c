/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:23:34 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/03/19 18:59:31 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "vector.h"

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
	return (res_normal);
}
