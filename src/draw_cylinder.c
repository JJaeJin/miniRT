/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:45:27 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/02 11:42:36by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "draw.h"
#include <math.h>

static void		get_p_side(t_vector v, t_point *p, t_obj_cylinder *cy);
static void		get_p_bottom(t_vector v, t_point *p, t_obj_cylinder *cy);
static double	get_height_diff(t_vector v_ray, t_obj_cylinder *cy);
static double	get_d_between_lines(t_vector v_ray, t_obj_cylinder *cy);
static t_point	get_p_center(t_obj_cylinder *cy, t_vector v);

void	check_cylinder(t_color *rgb, double *distance, t_vector v, t_info info)
{
	t_point			p_bottom[2];
	t_point			p_side[2];
	t_obj_cylinder	*cy;
	double			dis_between_lines;
	double			d_res;

	cy = info.objs->cy;
	while (cy != NULL)
	{
		dis_between_lines = get_d_between_lines(v, cy);
		if (dis_between_lines <= cy->diameter / 2)
		{
			get_p_side(v, p_side, cy);
			get_p_bottom(v, p_bottom, cy);
			
			d_res = v_size((t_vector)p_bottom[0]);
			if (p_get_distance(cy->loc, p_bottom[0]) <= \
				sqrt(pow(cy->diameter / 2, 2) + pow(cy->height / 2, 2)) \
				&& (*distance == 0 || d_res < *distance))
			{
				*distance = d_res;
				*rgb = cy->color;
			}
			d_res = v_size((t_vector)p_bottom[1]);
			if (p_get_distance(cy->loc, p_bottom[1]) <= \
				sqrt(pow(cy->diameter / 2, 2) + pow(cy->height / 2, 2)) \
				&& (*distance == 0 || d_res < *distance))
			{
				*distance = d_res;
				*rgb = cy->color;
			}
			d_res = v_size((t_vector)p_side[0]);
			if (sqrt(pow(p_get_distance(p_side[0], cy->loc), 2) - pow(cy->diameter / 2, 2)) <= cy->height / 2 && (*distance == 0 || d_res < *distance))
			{
				*distance = d_res;
				*rgb = cy->color;
			}
			d_res = v_size((t_vector)p_side[1]);
			if (sqrt(pow(p_get_distance(p_side[1], cy->loc), 2) - pow(cy->diameter / 2, 2)) <= cy->height / 2 && (*distance == 0 || d_res < *distance))
			{
				*distance = d_res;
				*rgb = cy->color;
			}
		}
		cy = cy->next;
	}
}

static void	get_p_bottom(t_vector v, t_point *p, t_obj_cylinder *cy)
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

static void	get_p_side(t_vector v, t_point *p, t_obj_cylinder *cy)
{
	t_point		center;
	double		height_diff;
	double		cy_to_center;
	double		t;
	t_vector	v_cy_to_center;
	t_point		temp;

	center = get_p_center(cy, v);
	height_diff = get_height_diff(v, cy);
	cy_to_center = p_get_distance(cy->loc, center);
	v_cy_to_center.x = center.x - cy->loc.x;
	v_cy_to_center.y = center.y - cy->loc.y;
	v_cy_to_center.z = center.z - cy->loc.z;
	v_normalize(&v_cy_to_center);
	temp.x = center.x - height_diff * v_cy_to_center.x;
	temp.y = center.y - height_diff * v_cy_to_center.y;
	temp.z = center.z - height_diff * v_cy_to_center.z;
	t = (v_cy_to_center.x * temp.x + v_cy_to_center.y * temp.y + v_cy_to_center.z * temp.z)
		/ (v_cy_to_center.x * v.x + v_cy_to_center.y * v.y + v_cy_to_center.z * v.z);
	p[0].x = t * v.x;
	p[0].y = t * v.y;
	p[0].z = t * v.z;
	temp.x = center.x + height_diff * v_cy_to_center.x;
	temp.y = center.y + height_diff * v_cy_to_center.y;
	temp.z = center.z + height_diff * v_cy_to_center.z;
	t = (v_cy_to_center.x * temp.x + v_cy_to_center.y * temp.y + v_cy_to_center.z * temp.z)
		/ (v_cy_to_center.x * v.x + v_cy_to_center.y * v.y + v_cy_to_center.z * v.z);
	p[1].x = t * v.x;
	p[1].y = t * v.y;
	p[1].z = t * v.z;
}

static double	get_height_diff(t_vector v_ray, t_obj_cylinder *cy)
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

// 두 직선 사이의 거리 구하기
static double	get_d_between_lines(t_vector v_ray, t_obj_cylinder *cy)
{
	t_vector	temp;
	double		t;
	t_point		p_on_cy;
	t_point		p_on_cam;
	
	temp = v_outer_product(v_ray, cy->normal);
	temp = v_outer_product(temp, v_ray);
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

// 원기둥 중심 직선에 시선 직선으로부터 내린 수선의 발
static t_point	get_p_center(t_obj_cylinder *cy, t_vector v)
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
