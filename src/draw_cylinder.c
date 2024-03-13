/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:45:27 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/12 20:45:36 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "draw.h"
#include <math.h>

static void	check_p_bottom(t_point p, t_obj_cylinder *cy, \
							double *distance, t_color *rgb);
static void	check_p_side(t_point p, t_obj_cylinder *cy, \
							double *distance, t_color *rgb);

void	check_cylinder(t_color *rgb, double *distance, t_vector v, t_info info)
{
	t_point			p_bottom[2];
	t_point			p_side[2];
	t_obj_cylinder	*cy;
	double			dis_between_lines;

	cy = info.objs->cy;
	while (cy != NULL)
	{
		dis_between_lines = get_d_between_lines(v, cy);
		if (dis_between_lines <= (cy->diameter / 2))
		{
			get_p_side(v, p_side, cy, info);
			get_p_bottom(v, p_bottom, cy);
			if (v_inner_product(p_bottom[0], info.camera->way) > 0)
				check_p_bottom(p_bottom[0], cy, distance, rgb);
			if (v_inner_product(p_bottom[1], info.camera->way) > 0)
				check_p_bottom(p_bottom[1], cy, distance, rgb);
			if (v_inner_product(p_side[0], info.camera->way) > 0)
				check_p_side(p_side[0], cy, distance, rgb);
			if (v_inner_product(p_side[1], info.camera->way) > 0)
				check_p_side(p_side[1], cy, distance, rgb);
		}
		cy = cy->next;
	}
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

double	get_d_between_lines(t_vector v_ray, t_obj_cylinder *cy)
{
	t_vector	temp;
	double		t;
	t_point		p_on_cy;
	t_point		p_on_cam;

	temp = v_outer_product(v_ray, cy->normal);
	if (temp.x == 0 && temp.y == 0 && temp.z == 0)
		return (0);
	temp = v_outer_product(temp, v_ray);
	if (v_inner_product(v_ray, cy->normal) == 0)
		return (v_size(cy->loc) * sqrt(1 - pow(v_inner_product(cy->loc, v_ray) \
				/ (v_size(cy->loc) * v_size(v_ray)), 2)));
	t = (-temp.x * cy->loc.x - temp.y * cy->loc.y - temp.z * cy->loc.z) / \
		(cy->normal.x * temp.x + cy->normal.y * temp.y + cy->normal.z * temp.z);
	p_on_cy.x = cy->loc.x + t * cy->normal.x;
	p_on_cy.y = cy->loc.y + t * cy->normal.y;
	p_on_cy.z = cy->loc.z + t * cy->normal.z;
	temp = v_outer_product(v_ray, cy->normal);
	t = (temp.y * p_on_cy.x - temp.x * p_on_cy.y) / \
		(v_ray.x * temp.y - v_ray.y * temp.x);
	p_on_cam.x = t * v_ray.x;
	p_on_cam.y = t * v_ray.y;
	p_on_cam.z = t * v_ray.z;
	return (p_get_distance(p_on_cy, p_on_cam));
}

static void	check_p_bottom(t_point p, t_obj_cylinder *cy, \
							double *distance, t_color *rgb)
{
	double	d_res;

	d_res = v_size(p);
	if (p_get_distance(cy->loc, p) <= \
		sqrt(pow(cy->diameter / 2, 2) + pow(cy->height / 2, 2)) \
		&& (*distance == 0 || d_res < *distance))
	{
		*distance = d_res;
		*rgb = cy->color;
	}
}

static void	check_p_side(t_point p, t_obj_cylinder *cy, \
							double *distance, t_color *rgb)
{
	double	d_res;

	d_res = v_size(p);
	if (sqrt(fabs(pow(p_get_distance(p, cy->loc), 2) - \
		pow(cy->diameter / 2, 2))) <= cy->height / 2 \
		&& (*distance == 0 || d_res < *distance))
	{
		*distance = d_res;
		*rgb = cy->color;
	}	
}
