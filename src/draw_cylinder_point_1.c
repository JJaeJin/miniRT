/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder_point_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:28:29 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/13 09:46:58 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include <math.h>
#include <stdio.h>

static void	get_p_side_parallel(t_vector v, t_obj_cylinder *cy, \
									t_point *p, t_vector cam);
static void	get_p_side_vertical(t_vector v, t_obj_cylinder *cy, \
									t_point *p, t_vector cam);

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

void	get_p_side(t_vector v, t_point *p, t_obj_cylinder *cy, t_info info)
{
	if (get_d_between_lines(v, cy) == 0)
		return (get_p_side_vertical(v, cy, p, info.camera->way));
	else if (v_inner_product(v, cy->normal) == 0)
		return (get_p_side_parallel(v, cy, p, info.camera->way));
	else
		return (get_p_side_others(v, p, cy));
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
	center.x = cy->loc.x + t * cy->normal.x;
	center.y = cy->loc.y + t * cy->normal.y;
	center.z = cy->loc.z + t * cy->normal.z;
	return (center);
}

static void	get_p_side_vertical(t_vector v, t_obj_cylinder *cy, \
								t_point *p, t_vector cam)
{
	t_point	center;
	double	cos_th1;
	double	sin_th2;
	double	diff;
	double	t;

	cos_th1 = v_inner_product(v, cam) / (v_size(v) * v_size(cam));
	t = get_d_between_lines(v_outer_product(cam, cy->normal), cy) \
		/ cos_th1;
	center.x = v.x * t;
	center.y = v.y * t;
	center.z = v.z * t;
	sin_th2 = sqrt(1 - pow(v_inner_product(v, cy->normal) \
					/ (v_size(v) * v_size(cy->normal)), 2));
	diff = (cy->diameter / 2) / sin_th2;
	v_normalize(&v);
	p[0].x = center.x - v.x * diff;
	p[0].y = center.y - v.y * diff;
	p[0].z = center.z - v.z * diff;
	p[1].x = center.x + v.x * diff;
	p[1].y = center.y + v.y * diff;
	p[1].z = center.z + v.z * diff;
}

static void	get_p_side_parallel(t_vector v, t_obj_cylinder *cy, \
									t_point *p, t_vector cam)
{
	double	def;
	double	diff;
	double	cos_th;
	double	v_to_cy;

	(void)cam;
	v_to_cy = get_d_between_lines(v, cy);
	cos_th = fabs(v_inner_product(cy->loc, cy->normal)) \
				/ (v_size(cy->loc) * v_size(cy->normal));
	def = sqrt(fabs(pow(v_size(cy->loc) * sqrt(1 - pow(cos_th, 2)), 2) \
				- pow(v_to_cy, 2)));
	diff = sqrt(fabs(pow(cy->diameter / 2, 2) - pow(v_to_cy, 2)));
	p[0].x = v.x * (def + diff);
	p[0].y = v.y * (def + diff);
	p[0].z = v.z * (def + diff);
	p[1].x = v.x * (def - diff);
	p[1].y = v.y * (def - diff);
	p[1].z = v.z * (def - diff);
}
