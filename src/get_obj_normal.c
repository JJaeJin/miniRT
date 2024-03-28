/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:23:34 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/03/26 20:55:19 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "vector.h"
#include <math.h>

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

t_vector	get_cone_normal(t_obj_cone *co, t_point p)
{
	t_vector	reverse_normal;
	t_vector	top_of_cone;
	t_vector	v_top_to_p;
	t_vector	res_normal;

	reverse_normal = v_multiply(co->normal, (-1));
	top_of_cone = v_add(co->loc, v_multiply(co->normal, co->height));
	v_top_to_p = p_get_vector(top_of_cone, p);
	res_normal = p_get_vector(v_multiply(reverse_normal, \
					pow(v_size(v_top_to_p), 2) / v_inner_product(v_top_to_p, \
					reverse_normal)), v_top_to_p);
	v_normalize(&res_normal);
	return (res_normal);
}
