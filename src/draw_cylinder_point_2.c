/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder_point_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:43:15 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/12 10:37:23 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include <math.h>

static void	set_temp(t_point *temp, t_point center, \
					t_vector v_cy_to_center, double height_diff);
static void	set_p(t_point *p, double t, t_vector v);

void	get_p_side_others(t_vector v, t_point *p, t_obj_cylinder *cy)
{
	t_point		center;
	double		height_diff;
	double		t;
	t_vector	v_cy_to_center;
	t_point		temp;

	center = get_p_center(cy, v);
	v_cy_to_center.x = center.x - cy->loc.x;
	v_cy_to_center.y = center.y - cy->loc.y;
	v_cy_to_center.z = center.z - cy->loc.z;
	height_diff = get_height_diff(v, cy);
	v_normalize(&v_cy_to_center);
	set_temp(&temp, center, v_cy_to_center, height_diff);
	t = (v_cy_to_center.x * temp.x + v_cy_to_center.y * temp.y \
		+ v_cy_to_center.z * temp.z) / (v_cy_to_center.x * v.x \
		+ v_cy_to_center.y * v.y + v_cy_to_center.z * v.z);
	set_p(&p[0], t, v);
	set_temp(&temp, center, v_cy_to_center, -height_diff);
	t = (v_cy_to_center.x * temp.x + v_cy_to_center.y * temp.y \
		+ v_cy_to_center.z * temp.z) / (v_cy_to_center.x * v.x \
		+ v_cy_to_center.y * v.y + v_cy_to_center.z * v.z);
	set_p(&p[1], t, v);
}

static void	set_temp(t_point *temp, t_point center, \
					t_vector v_cy_to_center, double height_diff)
{
	temp->x = center.x - height_diff * v_cy_to_center.x;
	temp->y = center.y - height_diff * v_cy_to_center.y;
	temp->z = center.z - height_diff * v_cy_to_center.z;
}

static void	set_p(t_point *p, double t, t_vector v)
{
	p->x = t * v.x;
	p->y = t * v.y;
	p->z = t * v.z;
}
