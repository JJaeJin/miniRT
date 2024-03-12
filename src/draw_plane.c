/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:45:29 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/12 19:59:19 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "draw.h"
#include <math.h>

void	check_plane(t_color *rgb, double *distance, t_vector v, t_info info)
{
	t_point			p_res;
	t_obj_plane		*pl;
	double			d_res;
	double			t;

	pl = info.objs->pl;
	while (pl != NULL)
	{
		if (v_inner_product(info.camera->way, pl->normal) != 0)
		{
			t = (pl->normal.x * pl->loc.x + pl->normal.y * pl->loc.y + \
				pl->normal.z * pl->loc.z) / (pl->normal.x * v.x + pl->normal.y \
				* v.y + pl->normal.z * v.z);
			p_res.x = v.x * t;
			p_res.y = v.y * t;
			p_res.z = v.z * t;
			d_res = v_size((t_vector)p_res);
			if (v_inner_product(p_res, info.camera->way) > 0 && (*distance == 0 || d_res < *distance))
			{
				*distance = d_res;
				*rgb = pl->color;
			}
		}
		pl = pl->next;
	}
}
