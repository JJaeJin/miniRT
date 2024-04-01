/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:10:36 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/03/31 20:49:29 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "vector.h"
#include "libft.h"
#include <math.h>

static int		co_check_p_bottom(double d_res, t_obj_cone *co, \
									double *distance, t_point p_bottom);
static void		co_apply_rgb_bottom(t_final_c *rgb, t_point p, \
									t_info info, t_obj_cone *co);
static void		co_apply_rgb_side(t_final_c *rgb, t_point p, \
									t_info info, t_obj_cone *co);

void	check_cone(t_final_c *rgb, double *distance, \
								t_vector v, t_info info)
{
	t_point		p_bottom;
	t_point		p_side[2];
	t_obj_cone	*co;
	double		*diff;
	double		d_res;

	co = info.objs->co;
	while (co != NULL)
	{
		diff = co_get_diff_set_p_side(p_side, v, co);
		if (diff != NULL)
		{
			d_res = co_get_distance(p_side, co, info.camera->way, v);
			if (co_check_p_side(d_res, distance, diff))
				co_apply_rgb_side(rgb, p_side[0], info, co);
		}
		co_get_p_bottom(v, &p_bottom, co);
		if (v_inner_product(p_bottom, info.camera->way) > 0)
		{
			d_res = v_size(p_bottom);
			if (co_check_p_bottom(d_res, co, distance, p_bottom))
				co_apply_rgb_bottom(rgb, p_bottom, info, co);
		}
		co = co->next;
	}
}

void	co_get_p_bottom(t_vector v, t_point *p, t_obj_cone *co)
{
	double	t;

	t = (co->normal.x * co->loc.x + co->normal.y * co->loc.y + co->normal.z \
		* co->loc.z) / (co->normal.x * v.x + co->normal.y * v.y + co->normal.z \
		* v.z);
	p->x = t * v.x;
	p->y = t * v.y;
	p->z = t * v.z;
}

static int	co_check_p_bottom(double d_res, t_obj_cone *co, \
							double *distance, t_point p_bottom)
{
	if (p_get_distance(co->loc, p_bottom) <= co->diameter / 2 \
		&& (*distance == 0 || d_res < *distance))
	{
		*distance = d_res;
		return (TRUE);
	}
	return (FALSE);
}

static void	co_apply_rgb_bottom(t_final_c *rgb, t_point p, \
								t_info info, t_obj_cone *co)
{
	t_light		*l;
	t_obj_plane	pl_bottom;
	t_vector	vec_light;
	double		cos_th;

	pl_bottom.color = co->color;
	pl_bottom.normal = co->normal;
	pl_bottom.temp_normal = co->normal;
	rgb->color = co->color;
	apply_ambient(rgb, info.amb);
	l = info.lights;
	vec_light = p_get_vector(l->loc, p);
	if (p_is_in_co(l->loc, co) == 1)
		vec_light = p_get_vector(p, l->loc);
	while (l != NULL)
	{
		cos_th = v_get_cos(vec_light, pl_bottom.temp_normal);
		if (p_is_in_co(l->loc, co) * is_in_co(co) == 1 && cos_th > 0 && \
				check_obstacles(l->loc, p, info, (void *)co) == OBS_NOT_EXIST)
		{
			apply_diffuse(&rgb->ratio, l, cos_th);
			apply_specular(rgb, l, p, co->normal);
		}
		l = l->next;
	}
}

static void	co_apply_rgb_side(t_final_c *rgb, t_point p, \
								t_info info, t_obj_cone *co)
{
	t_light		*l;
	t_vector	n;
	double		cos_th;

	n = get_cone_normal(co, p);
	rgb->color = co->color;
	apply_ambient(rgb, info.amb);
	l = info.lights;
	rgb->specular.red = 0;
	rgb->specular.green = 0;
	rgb->specular.blue = 0;
	while (l != NULL)
	{
		cos_th = v_get_cos(p_get_vector(p, l->loc), n);
		if (p_is_in_co(l->loc, co) * is_in_co(co) == 1 && cos_th > 0 \
			&& check_obstacles(l->loc, p, info, (void *)co) == OBS_NOT_EXIST)
		{
			apply_diffuse(&rgb->ratio, l, cos_th);
			if (check_specular(l, p, n) == TRUE)
				apply_specular(rgb, l, p, n);
		}
		l = l->next;
	}
}
