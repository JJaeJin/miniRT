/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sphere_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:31:28 by jaejilee          #+#    #+#             */
/*   Updated: 2024/04/01 13:57:47 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument_bonus.h"
#include "draw_bonus.h"
#include "vector_bonus.h"
#include "libft.h"
#include <math.h>

static double	get_res_distance(t_vector v, t_obj_sphere *sp, t_vector cam);
static void		add_lights_sp(t_final_c *rgb, t_point p, \
							t_obj_sphere *sp, t_info info);

void	check_sphere(t_final_c *rgb, double *distance, \
						t_vector v, t_info info)
{
	t_obj_sphere	*sp;
	double			d_res;
	t_point			p_res;

	sp = info.objs->sp;
	while (sp != NULL)
	{
		if (v_size(sp->center) <= sp->diameter / 2 || \
			v_size(sp->center) * sqrt(1 - pow(v_get_cos(sp->center, v), 2)) \
					<= sp->diameter / 2)
		{
			d_res = get_res_distance(v, sp, info.camera->way);
			if (d_res != -1 && (*distance == 0 || d_res < *distance))
			{
				p_res = v_multiply(v, d_res);
				*distance = d_res;
				sp->temp_normal = get_sphere_normal(sp, p_res);
				get_cb_color_sp(sp, info, p_res, &rgb->color);
				apply_ambient(rgb, info.amb);
				add_lights_sp(rgb, p_res, sp, info);
			}
		}
		sp = sp->next;
	}
}

static double	get_res_distance(t_vector v, t_obj_sphere *sp, t_vector cam)
{
	double	*t;
	t_point	res_p[2];
	double	res;

	t = solve_quadratic(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2), -2 * v.x * \
		sp->center.x -2 * v.y * sp->center.y -2 * v.z * sp->center.z, \
		pow(sp->center.x, 2) + pow(sp->center.y, 2) + pow(sp->center.z, 2) - \
		pow(sp->diameter / 2, 2));
	res_p[0] = v_multiply(v, t[0]);
	res_p[1] = v_multiply(v, t[1]);
	free(t);
	res = -1;
	if (v_inner_product(cam, res_p[0]) > 0)
		res = v_size(res_p[0]);
	if (v_inner_product(cam, res_p[1]) > 0 && \
			(res == -1 || res > v_size(res_p[1])))
		res = v_size(res_p[1]);
	return (res);
}

static void	add_lights_sp(t_final_c *rgb, t_point p, \
							t_obj_sphere *sp, t_info info)
{
	t_light		*l;
	t_vector	n;
	double		cos_th;

	l = info.lights;
	n = get_sphere_normal(sp, p);
	while (l != NULL)
	{
		cos_th = v_get_cos(p_get_vector(p, l->loc), sp->temp_normal);
		if (cos_th > 0 && \
		check_obstacles(l->loc, p, info, (void *)sp) == OBS_NOT_EXIST)
		{
			apply_diffuse(&rgb->ratio, l, cos_th);
			apply_specular(rgb, l, p, sp->temp_normal);
		}
		l = l->next;
	}
}
