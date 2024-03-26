/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cone_point_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:20:41 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/03/26 13:43:41 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "vector.h"
#include "libft.h"
#include <math.h>
#include <stdio.h>

static void		co_get_res_p(t_point *res, t_vector v, double *diff);
static double	*co_get_diff_set_p_side(t_point *p, t_vector v, \
										t_obj_cone *co);
static double	co_get_res_distance(t_point *p, t_vector cam, double *diff);
static double	co_get_distance(t_point *p, double *diff, \
								t_info info, t_vector v);

int	co_check_p_side(t_point *p, t_vector v, double *distance, t_info info)
{
	t_obj_cone	*co;
	t_point		p_side[2];
	double		d_res;
	double		*diff;

	co = info.objs->co;
	diff = co_get_diff_set_p_side(p_side, v, co);
	d_res = co_get_distance(p_side, diff, info, v);
	if (d_res != -1 && (*distance == 0 || d_res < *distance))
	{
		*p = p_side[0];
		*distance = d_res;
		return (TRUE);
	}
	return (FALSE);
}

static double	co_get_distance(t_point *p, double *diff, \
											t_info info, t_vector v)
{
	double		res_d;
	double		temp;
	t_obj_cone	*co;

	if (diff == NULL)
		return (-1);
	co = info.objs->co;
	res_d = co_get_res_distance(p, info.camera->way, diff);
	temp = v_inner_product(v_add(v_multiply(v, res_d), \
			v_multiply(co->loc, (-1))), co->normal);
	if (temp < 0 || co->height < temp)
		return (-1);
	return (res_d);
}

static double	co_get_res_distance(t_point *p, t_vector cam, double *diff)
{
	double	temp;
	double	res_d;

	res_d = 0;
	if (v_inner_product(p[0], cam) > 0)
		res_d = v_size(p[0]);
	if (sizeof(diff) != sizeof(double) && v_inner_product(p[1], cam) > 0)
	{
		temp = v_size(p[1]);
		if (res_d == 0 || res_d > temp)
		{
			res_d = temp;
			p[0] = p[1];
		}
	}
	free(diff);
	return (res_d);
}

static void	co_get_res_p(t_point *res, t_vector v, double *diff)
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

static double	*co_get_diff_set_p_side(t_point *p, t_vector v, \
										t_obj_cone *co)
{
	t_vector	w;
	double		*diff;
	double		temp;

	w = v_add(co->loc, v_multiply(co->normal, co->height));
	temp = pow(co->diameter / 2, 2) / pow(co->height, 2);
	diff = solve_quadratic(v_inner_product(v, v) - (temp + 1) * \
							pow(v_inner_product(v, co->normal), 2), \
							(-2) * (v_inner_product(v, w) - (temp + 1) * \
							v_inner_product(v, co->normal) * \
							v_inner_product(w, co->normal)), \
							v_inner_product(w, w) - (temp + 1) * \
							pow(v_inner_product(w, co->normal), 2));
	if (diff == NULL)
		return (NULL);
	co_get_res_p(p, v, diff);
	return (diff);
}
