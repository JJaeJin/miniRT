/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder_point_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:28:29 by jaejilee          #+#    #+#             */
/*   Updated: 2024/04/01 11:35:19 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include <math.h>

static void	get_p_side_parallel(t_vector v, t_obj_cylinder *cy, \
									t_point *p, t_vector *move);

void	get_p_bottom(t_vector v, t_point *p, t_obj_cylinder *cy)
{
	double	height_diff;
	t_point	temp;
	double	t;

	height_diff = cy->height / 2;
	temp.x = cy->loc.x + height_diff * cy->normal.x;
	temp.y = cy->loc.y + height_diff * cy->normal.y;
	temp.z = cy->loc.z + height_diff * cy->normal.z;
	t = (cy->normal.x * temp.x + cy->normal.y * temp.y + cy->normal.z * temp.z)
		/ (cy->normal.x * v.x + cy->normal.y * v.y + cy->normal.z * v.z);
	p[0].x = t * v.x;
	p[0].y = t * v.y;
	p[0].z = t * v.z;
	temp.x = cy->loc.x - height_diff * cy->normal.x;
	temp.y = cy->loc.y - height_diff * cy->normal.y;
	temp.z = cy->loc.z - height_diff * cy->normal.z;
	t = (cy->normal.x * temp.x + cy->normal.y * temp.y + cy->normal.z * temp.z)
		/ (cy->normal.x * v.x + cy->normal.y * v.y + cy->normal.z * v.z);
	p[1].x = t * v.x;
	p[1].y = t * v.y;
	p[1].z = t * v.z;
}

void	get_p_side(t_vector v, t_point *p, t_obj_cylinder *cy)
{
	t_obj_cylinder	temp_cy;
	double			diff;
	t_vector		move;

	temp_cy = *cy;
	move.x = 0;
	move.y = 0;
	move.z = 0;
	if (is_in_cy(cy) == 1)
	{
		diff = sqrt(pow(cy->height, 2) + pow(cy->diameter, 2));
		move = v_multiply(v, diff / v_size(v));
		temp_cy.loc = v_add(cy->loc, move);
	}
	if (v_inner_product(v, cy->normal) == 0)
		return (get_p_side_parallel(v, &temp_cy, p, &move));
	else
		return (get_p_side_others(v, p, &temp_cy, &move));
}

t_point	get_p_center(t_obj_cylinder *cy, t_vector v)
{
	double		t;
	t_vector	temp;
	t_point		center;

	temp = v_outer_product(cy->normal, v);
	temp = v_outer_product(temp, v);
	t = (-temp.x * cy->loc.x - temp.y * cy->loc.y - temp.z * cy->loc.z) / \
		(cy->normal.x * temp.x + cy->normal.y * temp.y + cy->normal.z * temp.z);
	center = v_add(cy->loc, v_multiply(cy->normal, t));
	return (center);
}

double	get_height_diff(t_vector v_ray, t_obj_cylinder *cy)
{
	double		dis_between_lines;
	double		theta;
	double		res;

	dis_between_lines = get_d_between_lines(v_ray, cy);
	theta = acos(sqrt(1 - pow((v_inner_product(v_ray, cy->normal) / \
			(v_size(v_ray) * v_size(cy->normal))), 2)));
	res = sqrt(pow(cy->diameter / 2, 2) - pow(dis_between_lines, 2)) * \
			tan(theta);
	return (res);
}

static void	get_p_side_parallel(t_vector v, t_obj_cylinder *cy, \
								t_point *p, t_vector *move)
{
	double	def;
	double	diff;
	double	cos_th;
	double	v_to_cy;

	v_normalize(&v);
	v_to_cy = get_d_between_lines(v, cy);
	cos_th = fabs(v_inner_product(cy->loc, cy->normal)) \
				/ (v_size(cy->loc) * v_size(cy->normal));
	def = sqrt(pow(v_size(cy->loc), 2) - \
				pow(v_inner_product(cy->loc, cy->normal), 2) - pow(v_to_cy, 2));
	diff = sqrt(fabs(pow(cy->diameter / 2, 2) - pow(v_to_cy, 2)));
	p[0] = v_sub(v_multiply(v, def + diff), *move);
	p[1] = v_sub(v_multiply(v, def - diff), *move);
}
