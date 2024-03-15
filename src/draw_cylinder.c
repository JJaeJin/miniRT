/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:45:27 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/15 20:06:03 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "draw.h"
#include "libft.h"
#include <math.h>
#include <stdio.h>

static int		check_p_bottom(t_point p, t_obj_cylinder *cy, \
									double *distance, t_info info);
static int		check_p_side(t_point p, t_obj_cylinder *cy, \
									double *distance, t_info info);
static void		cy_apply_rgb_side(t_final_c *rgb, t_point p, \
									t_info info, t_obj_cylinder *cy);
static void		cy_apply_rgb_bottom(t_final_c *rgb, t_point p, \
									t_info info, t_obj_cylinder *cy);

void	check_cylinder(t_final_c *rgb, double *distance, \
								t_vector v, t_info info)
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
			get_p_side(v, p_side, cy);
			get_p_bottom(v, p_bottom, cy);
			if (check_p_bottom(p_bottom[0], cy, distance, info))
				cy_apply_rgb_bottom(rgb, p_bottom[0], info, cy);
			if (check_p_bottom(p_bottom[1], cy, distance, info))
				cy_apply_rgb_bottom(rgb, p_bottom[1], info, cy);
			if (check_p_side(p_side[0], cy, distance, info))
				cy_apply_rgb_side(rgb, p_side[0], info, cy);
			if (check_p_side(p_side[1], cy, distance, info))
				cy_apply_rgb_side(rgb, p_side[1], info, cy);
		}
		cy = cy->next;
	}
}

static int	check_p_bottom(t_point p, t_obj_cylinder *cy, \
							double *distance, t_info info)
{
	double	d_res;

	if (v_inner_product(p, info.camera->way) <= 0)
		return (FALSE);
	d_res = v_size(p);
	if (p_get_distance(cy->loc, p) <= \
		sqrt(pow(cy->diameter / 2, 2) + pow(cy->height / 2, 2)) \
		&& (*distance == 0 || d_res < *distance))
	{
		*distance = d_res;
		return (TRUE);
	}
	return (FALSE);
}

static int	check_p_side(t_point p, t_obj_cylinder *cy, \
						double *distance, t_info info)
{
	double	d_res;

	if (v_inner_product(p, info.camera->way) <= 0)
		return (FALSE);
	d_res = v_size(p);
	if (sqrt(fabs(pow(p_get_distance(p, cy->loc), 2) - \
		pow(cy->diameter / 2, 2))) <= cy->height / 2 \
		&& (*distance == 0 || d_res < *distance))
	{
		*distance = d_res;
		return (TRUE);
	}
	return (FALSE);
}

static void	cy_apply_rgb_side(t_final_c *rgb, t_point p, \
								t_info info, t_obj_cylinder *cy)
{
	t_light		*l;
	t_vector	n;
	double	cos_th;

	rgb->color = cy->color;
	apply_ambient(rgb, info.amb);
	l = info.lights;
	n = get_cylinder_normal(cy, p);
	while (l != NULL)
	{
		if (check_obstacles(l->loc, p, info, (void *)cy) == OBS_NOT_EXIST)
		{
			cos_th = v_get_cos(p_get_vector(p, l->loc), n);
			rgb->ratio.red += \
				l->color.red * l->ratio * cos_th / 255;
			rgb->ratio.green += \
				l->color.green * l->ratio * cos_th / 255;
			rgb->ratio.blue += \
				l->color.blue * l->ratio * cos_th / 255;
		}
		l = l->next;
	}
}

static void	cy_apply_rgb_bottom(t_final_c *rgb, t_point p, \
								t_info info, t_obj_cylinder *cy)
{
	t_light		*l;
	t_vector	n;
	double	cos_th;

	rgb->color = cy->color;
	apply_ambient(rgb, info.amb);
	l = info.lights;
	n = get_cylinder_normal_bottom(info.camera, cy);
	while (l != NULL)
	{
		if (check_obstacles(l->loc, p, info, (void *)cy) == OBS_NOT_EXIST)
		{
			cos_th = v_get_cos(p_get_vector(p, l->loc), n);
			printf("cos_th = %f\n", cos_th);
			rgb->ratio.red += \
				l->color.red * l->ratio * cos_th / 255;
			rgb->ratio.green += \
				l->color.green * l->ratio * cos_th / 255;
			rgb->ratio.blue += \
				l->color.blue * l->ratio * cos_th / 255;
		}
		l = l->next;
	}
}
