/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder_point_2_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:43:15 by jaejilee          #+#    #+#             */
/*   Updated: 2024/04/01 13:54:58 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument_bonus.h"
#include <math.h>

static void		set_temp(t_point *temp, t_point center, \
					t_vector v_cy_to_center, double height_diff);
static double	get_d_between_lines_parallel(t_vector v_ray, \
					t_obj_cylinder *cy);

void	get_p_side_others(t_vector v, t_point *p, \
					t_obj_cylinder *cy, t_vector *move)
{
	t_point		center;
	double		height_diff;
	double		t;
	t_vector	v_cy_to_center;
	t_point		temp;

	center = get_p_center(cy, v);
	v_cy_to_center = v_sub(center, cy->loc);
	height_diff = get_height_diff(v, cy);
	v_normalize(&v_cy_to_center);
	set_temp(&temp, center, v_cy_to_center, height_diff);
	t = (v_cy_to_center.x * temp.x + v_cy_to_center.y * temp.y \
		+ v_cy_to_center.z * temp.z) / (v_cy_to_center.x * v.x \
		+ v_cy_to_center.y * v.y + v_cy_to_center.z * v.z);
	p[0] = v_sub(v_multiply(v, t), *move);
	set_temp(&temp, center, v_cy_to_center, -height_diff);
	t = (v_cy_to_center.x * temp.x + v_cy_to_center.y * temp.y \
		+ v_cy_to_center.z * temp.z) / (v_cy_to_center.x * v.x \
		+ v_cy_to_center.y * v.y + v_cy_to_center.z * v.z);
	p[1] = v_sub(v_multiply(v, t), *move);
}

static void	set_temp(t_point *temp, t_point center, \
					t_vector v_cy_to_center, double height_diff)
{
	temp->x = center.x - height_diff * v_cy_to_center.x;
	temp->y = center.y - height_diff * v_cy_to_center.y;
	temp->z = center.z - height_diff * v_cy_to_center.z;
}

double	get_d_between_lines(t_vector v_ray, t_obj_cylinder *cy)
{
	t_vector	temp;
	double		t;
	t_point		p_on_cy;
	t_point		p_on_cam;

	temp = v_outer_product(v_ray, cy->normal);
	if (v_size(temp) == 0)
		return (0);
	if (v_size(v_outer_product(cy->cam, cy->normal)) == 0)
		return (fabs(temp.x * cy->loc.x + temp.y * cy->loc.y + \
		temp.z * cy->loc.z) / sqrt(pow(temp.x, 2) + \
		pow(temp.y, 2) + pow(temp.z, 2)));
	temp = v_outer_product(temp, v_ray);
	if (v_inner_product(v_ray, cy->normal) == 0)
		return (get_d_between_lines_parallel(v_ray, cy));
	t = (-temp.x * cy->loc.x - temp.y * cy->loc.y - temp.z * cy->loc.z) / \
		(cy->normal.x * temp.x + cy->normal.y * temp.y + cy->normal.z * temp.z);
	p_on_cy = v_add(cy->loc, v_multiply(cy->normal, t));
	temp = v_outer_product(v_ray, cy->normal);
	t = get_contact_t(temp, v_ray, p_on_cy);
	p_on_cam = v_multiply(v_ray, t);
	return (p_get_distance(p_on_cy, p_on_cam));
}

static double	get_d_between_lines_parallel(t_vector v_ray, t_obj_cylinder *cy)
{
	double	cos_th_1;
	double	sin_th_2;
	double	res;

	cos_th_1 = v_inner_product(cy->normal, cy->loc) \
				/ (v_size(cy->normal) * v_size(cy->loc));
	sin_th_2 = sqrt(1 - pow(v_inner_product(v_ray, cy->loc) \
				/ (v_size(v_ray) * v_size(cy->loc)), 2));
	res = v_size(cy->loc) * sqrt(fabs(pow(sin_th_2, 2) - pow(cos_th_1, 2)));
	return (res);
}

int	p_is_in_cy(t_point p, t_obj_cylinder *cy)
{
	double	h;
	double	d;

	h = fabs(v_inner_product(cy->normal, p_get_vector(cy->loc, p)));
	d = sqrt(pow(p_get_distance(cy->loc, p), 2) - pow(h, 2));
	if (d < cy->diameter / 2 && h < cy->height / 2)
		return (1);
	else
		return (-1);
}
