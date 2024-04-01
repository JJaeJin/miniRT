/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:23:34 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/03/31 20:26:50 by dongyeuk         ###   ########.fr       */
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
	if (v_size(sp->center) <= sp->diameter / 2)
		return (v_multiply(normal, -1));
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
	if (is_in_cy(cy) == 1)
		return (v_multiply(res_normal, -1));
	return (res_normal);
}

t_vector	get_cone_normal(t_obj_cone *co, t_point p)
{
	t_vector	reverse_normal;
	t_vector	temp_vector;
	t_vector	res_normal;
	double		temp;

	reverse_normal = v_multiply(co->normal, (-1));
	temp_vector = v_add(co->loc, v_multiply(co->normal, co->height));
	temp_vector = p_get_vector(temp_vector, p);
	res_normal = p_get_vector(v_multiply(reverse_normal, \
					pow(v_size(temp_vector), 2) / v_inner_product(temp_vector, \
					reverse_normal)), temp_vector);
	v_normalize(&res_normal);
	if (v_size(co->loc) != 0)
	{
		temp = 1 - pow(v_inner_product(co->loc, co->normal) / \
				v_size(co->loc), 2);
		temp = pow(temp * v_size(co->loc), 2) - \
				pow((1 - v_inner_product(co->loc, co->normal) / \
				co->height) * co->diameter / 2, 2);
		if (get_sign(temp) == -1)
			res_normal = v_multiply(res_normal, (-1));
	}
	return (res_normal);
}
