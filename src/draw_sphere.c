/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:31:28 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/19 16:55:13 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "draw.h"
#include "vector.h"
#include "libft.h"
#include <math.h>

static double	get_res_distance(t_vector v, t_obj_sphere *sp, t_vector cam);
static void		get_res_p(t_point *res, t_vector v, double *diff);
static t_point	sp_get_p(t_point p, double d_res);
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
		if (v_size((t_vector)sp->center) * sqrt(1 - \
			pow(v_inner_product((t_vector)sp->center, v) / \
			(v_size((t_vector)sp->center) * v_size(v)), 2)) <= sp->diameter / 2)
		{
			d_res = get_res_distance(v, sp, info.camera->way);
			if (d_res != -1 && (*distance == 0 || d_res < *distance))
			{
				p_res = sp_get_p(v, d_res);
				*distance = d_res;
				rgb->color = sp->color;
				apply_ambient(rgb, info.amb);
				add_lights_sp(rgb, p_res, sp, info);
			}
		}
		sp = sp->next;
	}
}

static double	get_res_distance(t_vector v, t_obj_sphere *sp, t_vector cam)
{
	t_point	res[2];
	double	*diff;
	double	res_d;
	double	temp;

	res_d = 0;
	diff = solve_quadratic(pow(v.x, 2) + pow(v.y, 2) + \
				pow(v.z, 2), -2 * v.x * sp->center.x -2 * v.y * \
				sp->center.y -2 * v.z * sp->center.z, pow(sp->center.x, 2) \
				+ pow(sp->center.y, 2) + pow(sp->center.z, 2) - \
				pow(sp->diameter / 2, 2));
	if (diff == NULL)
		return (-1);
	get_res_p(res, v, diff);
	if (v_inner_product(res[0], cam) > 0)
		res_d = v_size(res[0]);
	if (sizeof(diff) != sizeof(double) && v_inner_product(res[1], cam) > 0)
	{
		temp = v_size(res[1]);
		if (res_d == 0 || res_d > temp)
			res_d = temp;
	}
	free(diff);
	return (res_d);
}

static void	get_res_p(t_point *res, t_vector v, double *diff)
{
	res[0].x = v.x * diff[0];
	res[0].y = v.y * diff[0];
	res[0].z = v.z * diff[0];
	if (sizeof(diff) == sizeof(double))
		return ;
	res[1].x = v.x * diff[1];
	res[1].y = v.y * diff[1];
	res[1].z = v.z * diff[1];
}

static t_point	sp_get_p(t_point p, double d_res)
{
	t_point	res;

	res.x = p.x * d_res;
	res.y = p.y * d_res;
	res.z = p.z * d_res;
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
		cos_th = v_get_cos(p_get_vector(p, l->loc), n);
		if (cos_th > 0 && \
				check_obstacles(l->loc, p, info, (void *)sp) == OBS_NOT_EXIST)
		{
			apply_diffuse(&rgb->ratio, l, cos_th);
			apply_specular(rgb, l, p, n);
		}
		l = l->next;
	}
}
