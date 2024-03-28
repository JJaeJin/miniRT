/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_obstacles_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:39:15 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/03/26 15:22:59 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "vector.h"
#include "libft.h"
#include <math.h>

static int	is_obstacle_co(t_point *p, t_obj_cone *m_co, t_point m_l);
static void	co_get_p_side(t_point *p, t_vector v, t_obj_cone *co);
static void	co_get_res_p(t_point *res, t_vector v, double *diff);

int	check_obs_cone(t_point l, t_point p, t_obj_cone *co, void *obj)
{
	t_obj_cone	*temp_co;
	t_obj_cone	modified_co;
	t_point		modified_l;
	t_point		p_cone[2];

	temp_co = co;
	while (temp_co != NULL)
	{
		if ((void *)temp_co != obj)
		{
			modified_l = p_get_vector(p, l);
			modified_co = *temp_co;
			modified_co.loc = p_get_vector(p, modified_co.loc);
			co_get_p_side(p_cone, modified_l, &modified_co);
			co_get_p_bottom(modified_l, &p_cone[1], &modified_co);
			if (is_obstacle_co(p_cone, &modified_co, modified_l) \
				== OBS_EXIST)
				return (OBS_EXIST);
		}
		temp_co = temp_co->next;
	}
	return (OBS_NOT_EXIST);
}

static int	is_obstacle_co(t_point *p, t_obj_cone *m_co, t_point m_l)
{
	t_vector	unit_m_l;
	double		temp;

	if (v_inner_product(p[1], m_l) > 0 && p_get_distance(p[1], m_co->loc) <= \
		m_co->diameter / 2 && v_size(m_l) > v_size(p[1]))
		return (OBS_EXIST);
	unit_m_l = m_l;
	v_normalize(&unit_m_l);
	if (v_inner_product(p[0], m_l) > 0 && v_size(m_l) > v_size(p[0]))
	{
		temp = v_inner_product(v_add(v_multiply(unit_m_l, v_size(p[0])), \
			v_multiply(m_co->loc, (-1))), m_co->normal);
		if (temp >= 0 && m_co->height >= temp)
			return (OBS_EXIST);
	}
	return (OBS_NOT_EXIST);
}

static void	co_get_p_side(t_point *p, t_vector v, t_obj_cone *co)
{
	t_vector	w;
	double		*diff;
	double		temp;

	w = v_add(co->loc, v_multiply(co->normal, co->height));
	temp = pow(co->diameter / 2, 2) / pow(co->height, 2);
	diff = solve_quadratic(v_inner_product(v, v) - (temp + 1) * \
							pow(v_inner_product(v, co->normal), 2), (-2) * \
							(v_inner_product(v, w) - (temp + 1) * \
							v_inner_product(v, co->normal) * \
							v_inner_product(w, co->normal)), \
							v_inner_product(w, w) - (temp + 1) * \
							pow(v_inner_product(w, co->normal), 2));
	co_get_res_p(p, v, diff);
}

static void	co_get_res_p(t_point *res, t_vector v, double *diff)
{
	if (diff == NULL)
	{
		res[0].x = 0;
		res[0].y = 0;
		res[0].z = 0;
		return ;
	}
	res[0].x = v.x * diff[0];
	res[0].y = v.y * diff[0];
	res[0].z = v.z * diff[0];
}
