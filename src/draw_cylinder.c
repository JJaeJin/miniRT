/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:45:27 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/29 19:15:53 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "draw.h"
#include "libft.h"
#include <math.h>

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
	if (v_inner_product(p, cy->normal) > 0)
		cy->normal = v_multiply(cy->normal, -1);
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
	if ((sqrt(fabs(pow(p_get_distance(p, cy->loc), 2) - \
		pow(cy->diameter / 2, 2))) <= cy->height / 2 \
		&& (*distance == 0 || d_res < *distance)))
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
	double		cos_th;
	t_vector	n;

	n = get_cylinder_normal(cy, p);
	cy->temp_normal = n;
	rgb->color = cy->color;
	apply_ambient(rgb, info.amb);
	l = info.lights;
	rgb->specular.red = 0;
	rgb->specular.green = 0;
	rgb->specular.blue = 0;
	while (l != NULL)
	{
		cos_th = v_get_cos(p_get_vector(p, l->loc), cy->temp_normal);
		if (p_is_in_cy(l->loc, cy) * is_in_cy(cy) == 1 && \
			cos_th >= 0 && \
			check_obstacles(l->loc, p, info, (void *)cy) == OBS_NOT_EXIST)
		{
			apply_diffuse(&rgb->ratio, l, cos_th);
			if (check_specular(l, p, n) == TRUE)
				apply_specular(rgb, l, p, cy->temp_normal);
		}
		l = l->next;
	}
}

static void	cy_apply_rgb_bottom(t_final_c *rgb, t_point p, \
								t_info info, t_obj_cylinder *cy)
{
	t_light		*l;
	t_obj_plane	pl_bottom;
	double		cos_th;

	pl_bottom.color = cy->color;
	if (v_inner_product(p_get_vector(cy->loc, p), cy->normal) > 0)
		pl_bottom.loc = v_add(cy->loc, v_multiply(cy->normal, cy->height / 2));
	else
		pl_bottom.loc = v_sub(cy->loc, v_multiply(cy->normal, cy->height / 2));
	pl_bottom.normal = cy->normal;
	pl_bottom.temp_normal = cy->normal;
	rgb->color = cy->color;
	apply_ambient(rgb, info.amb);
	l = info.lights;
	while (l != NULL)
	{
		cos_th = v_get_cos(p_get_vector(p, l->loc), pl_bottom.temp_normal);
		if (cos_th > 0 && \
		check_obstacles(l->loc, p, info, (void *)cy) == OBS_NOT_EXIST)
		{
			apply_diffuse(&rgb->ratio, l, cos_th);
			apply_specular(rgb, l, p, pl_bottom.temp_normal);
		}
		l = l->next;
	}
}
