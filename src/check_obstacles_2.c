/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_obstacles_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:33:58 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/17 16:35:14 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "vector.h"
#include <math.h>

static int		is_obstacle_cy(t_point *p, t_obj_cylinder *m_cy, t_point m_l);

int	check_obs_cylinder(t_point l, t_point p, t_obj_cylinder *cy, void *obj)
{
	t_obj_cylinder	*temp_cy;
	t_obj_cylinder	modified_cy;
	t_point			modified_l;
	t_point			p_bottom_side[4];

	temp_cy = cy;
	while (temp_cy != NULL)
	{
		if ((void *)temp_cy != obj)
		{
			modified_l = p_get_vector(p, l);
			modified_cy = *temp_cy;
			modified_cy.loc = p_get_vector(p, modified_cy.loc);
			get_p_bottom(modified_l, p_bottom_side, &modified_cy);
			get_p_side(modified_l, p_bottom_side + 2, &modified_cy);
			if (is_obstacle_cy(p_bottom_side, &modified_cy, modified_l) \
				== OBS_EXIST)
				return (OBS_EXIST);
		}
		temp_cy = temp_cy->next;
	}
	return (OBS_NOT_EXIST);
}

static int	is_obstacle_cy(t_point *p, t_obj_cylinder *m_cy, t_point m_l)
{
	double	d_res;

	d_res = v_size(p[0]);
	if (v_inner_product(p[0], m_l) > 0 && p_get_distance(m_cy->loc, m_l) <= \
		sqrt(pow(m_cy->diameter / 2, 2) + pow(m_cy->height / 2, 2)) && \
		v_size(m_l) > v_size(p[0]))
		return (OBS_EXIST);
	d_res = v_size(p[1]);
	if (v_inner_product(p[1], m_l) > 0 && p_get_distance(m_cy->loc, m_l) <= \
		sqrt(pow(m_cy->diameter / 2, 2) + pow(m_cy->height / 2, 2)) && \
		v_size(m_l) > v_size(p[1]))
		return (OBS_EXIST);
	d_res = v_size(p[2]);
	if (v_inner_product(p[2], m_l) > 0 && \
		sqrt(fabs(pow(p_get_distance(p[2], m_cy->loc), 2) - \
		pow(m_cy->diameter / 2, 2))) <= m_cy->height / 2 && \
		v_size(m_l) > v_size(p[2]))
		return (OBS_EXIST);
	d_res = v_size(p[3]);
	if (v_inner_product(p[3], m_l) > 0 && \
		sqrt(fabs(pow(p_get_distance(p[3], m_cy->loc), 2) - \
		pow(m_cy->diameter / 2, 2))) <= m_cy->height / 2 && \
		v_size(m_l) > v_size(p[3]))
		return (OBS_EXIST);
	return (OBS_NOT_EXIST);
}
