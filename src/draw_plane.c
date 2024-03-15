/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:45:29 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/15 19:53:56 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "draw.h"
#include <math.h>

static void	get_p_res(double t, t_point *p_res, t_vector v);
static void	add_lights_pl(t_final_c *rgb, t_point p, \
							t_obj_plane *pl, t_info info);

void	check_plane(t_final_c *rgb, double *distance, t_vector v, t_info info)
{
	t_point			p_res;
	t_obj_plane		*pl;
	double			d_res;

	pl = info.objs->pl;
	while (pl != NULL)
	{
		if (v_inner_product(info.camera->way, pl->normal) != 0)
		{
			get_p_res((pl->normal.x * pl->loc.x + pl->normal.y * pl->loc.y + \
				pl->normal.z * pl->loc.z) / (pl->normal.x * v.x + pl->normal.y \
				* v.y + pl->normal.z * v.z), &p_res, v);
			d_res = v_size((t_vector)p_res);
			if (v_inner_product(p_res, info.camera->way) > 0 \
				&& (*distance == 0 || d_res < *distance))
			{
				*distance = d_res;
				rgb->color = pl-> color;
				apply_ambient(rgb, info.amb);
				add_lights_pl(rgb, p_res, pl, info);
			}
		}
		pl = pl->next;
	}
}

static void	get_p_res(double t, t_point *p_res, t_vector v)
{
	p_res->x = v.x * t;
	p_res->y = v.y * t;
	p_res->z = v.z * t;
}

static void	add_lights_pl(t_final_c *rgb, t_point p, \
							t_obj_plane *pl, t_info info)
{
	t_light		*l;
	t_vector	n;
	double	cos_th;

	l = info.lights;
	n = get_plane_normal(info.camera, pl);
	while (l != NULL)
	{
		if (check_obstacles(l->loc, p, info, (void *)pl) == OBS_NOT_EXIST)
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

