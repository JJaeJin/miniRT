/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:31:28 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/12 19:53:06 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "draw.h"
#include "vector.h"
#include <math.h>

static double	get_res_distance(t_vector v, t_obj_sphere *sp, t_vector cam);

void	check_sphere(t_color *rgb, double *distance, t_vector v, t_info info)
{
	double			d;
	double			cos_th;
	t_obj_sphere	*sp;
	double			d_res;

	sp = info.objs->sp;
	while (sp != NULL)
	{
		d = v_size((t_vector)sp->center);
		cos_th = v_inner_product((t_vector)sp->center, v) \
				/ (v_size((t_vector)sp->center) * v_size(v));
		if (d * sqrt(1 - pow(cos_th, 2)) <= sp->diameter / 2)
		{
			d_res = get_res_distance(v, sp, info.camera->way);
			if (*distance == 0 || d_res < *distance)
			{
				*distance = d_res;
				*rgb = sp->color;
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
	res[0].x = v.x * diff[0];
	res[0].y = v.y * diff[0];
	res[0].z = v.z * diff[0];
	res[1].x = v.x * diff[1];
	res[1].y = v.y * diff[1];
	res[1].z = v.z * diff[1];
	if (v_inner_product(res[0], cam) > 0)
		res_d = v_size(res[0]);
	if (v_inner_product(res[1], cam) > 0)
	{
		temp = v_size(res[1]);
		if (res_d == 0 || res_d > temp)
			res_d = temp;
	}
	free(diff);
	return (res_d);
}
