/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_checkerboard_color_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 10:02:34 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/24 15:48:19 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "vector.h"
#include <math.h>

static t_point	get_cs_cy_side(t_point p, t_vector v_cy, t_vector v_z);

void	get_cb_color_cy_side(t_obj_cylinder *cy, t_info info, \
								t_point p, t_color *c)
{
	t_point		p_converted;
	t_vector	v_z;
	int			d;
	double		sign;

	if (info.checkerboard == 0)
	{
		*c = cy->color;
		return ;
	}
	v_z.x = 0;
	v_z.y = 0;
	v_z.z = 1;
	p = v_sub(p, cy->loc);
	p_converted = get_cs_cy_side(p, cy->normal, v_z);
	d = (abs((int)(p_converted.x / (M_PI / 30))) + \
		abs((int)(p_converted.y / 10))) % 2;
	sign = get_sign(p_converted.x) * get_sign(p_converted.y);
	if ((sign < 0 && d == 1) || (sign >= 0 && d == 0))
		*c = cy->color;
	else
		*c = get_complementary_color(cy->color);
}

static t_point	get_cs_cy_side(t_point p, t_vector v_cy, t_vector v_z)
{
	t_point		res;
	t_point		temp;
	t_vector	n;
	double		cos_th;

	n = v_outer_product(v_z, v_cy);
	if (v_size(n) != 0)
	{
		v_normalize(&n);
		cos_th = v_get_cos(v_z, n);
		temp = v_add(v_add(v_multiply(p, cos_th), v_multiply(n, (1 - cos_th) \
			* v_inner_product(p, n))), \
			v_multiply(v_outer_product(n, p), sqrt(1 - pow(cos_th, 2))));
	}
	else
		temp = p;
	res.y = temp.z;
	temp.z = 0;
	if (temp.y < 0)
		res.x = acos(temp.x / v_size(temp));
	else
		res.x = -acos(temp.x / v_size(temp));
	return (res);
}
