/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_obstacles_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:33:58 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/25 14:03:08 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "vector.h"
#include <math.h>

static int	is_obstacle_cy(t_point *p, t_obj_cylinder *m_cy, t_point m_l);

int	check_obs_cylinder(t_point l, t_point p, t_obj_cylinder *cy, void *obj)
{
	t_obj_cylinder	*temp_cy;
	t_obj_cylinder	m_cy;
	t_point			m_l;
	t_point			p_bottom_side[4];

	temp_cy = cy;
	while (temp_cy != NULL)
	{
		if ((void *)temp_cy != obj)
		{
			m_l = p_get_vector(p, l);
			m_cy = *temp_cy;
			m_cy.loc = p_get_vector(p, m_cy.loc);
			if (get_d_between_lines(p, temp_cy) <= (temp_cy->diameter / 2))
			{
				get_p_bottom(v_multiply(m_l, -1), p_bottom_side, &m_cy);
				get_p_side(v_multiply(m_l, -1), p_bottom_side + 2, &m_cy);
				if (is_obstacle_cy(p_bottom_side, &m_cy, m_l) \
					== OBS_EXIST)
					return (OBS_EXIST);
			}
		}
		temp_cy = temp_cy->next;
	}
	return (OBS_NOT_EXIST);
}

static int	is_obstacle_cy(t_point *p, t_obj_cylinder *m_cy, t_point m_l)
{
	if (v_inner_product(p[0], m_l) > 0 && p_get_distance(m_cy->loc, m_l) <= \
		sqrt(pow(m_cy->diameter / 2, 2) + pow(m_cy->height / 2, 2)) && \
		v_size(m_l) > v_size(p[0]))
		return (OBS_EXIST);
	if (v_inner_product(p[1], m_l) > 0 && p_get_distance(m_cy->loc, m_l) <= \
		sqrt(pow(m_cy->diameter / 2, 2) + pow(m_cy->height / 2, 2)) && \
		v_size(m_l) > v_size(p[1]))
		return (OBS_EXIST);
	if (v_inner_product(p[2], m_l) > 0 && \
		sqrt(fabs(pow(p_get_distance(p[2], m_cy->loc), 2) - \
		pow(m_cy->diameter / 2, 2))) <= m_cy->height / 2 && \
		v_size(m_l) > v_size(p[2]))
		return (OBS_EXIST);
	if (v_inner_product(p[3], m_l) > 0 && \
		sqrt(fabs(pow(p_get_distance(p[3], m_cy->loc), 2) - \
		pow(m_cy->diameter / 2, 2))) <= m_cy->height / 2 && \
		v_size(m_l) > v_size(p[3]))
		return (OBS_EXIST);
	return (OBS_NOT_EXIST);
}
