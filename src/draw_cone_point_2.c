/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cone_point_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:31:06 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/03/31 15:54:43 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "vector.h"
#include "libft.h"
#include <math.h>

int	p_is_in_co(t_point p, t_obj_cone *co)
{
	double	h;
	double	d;

	h = v_inner_product(co->normal, p_get_vector(co->loc, p));
	d = sqrt(pow(p_get_distance(co->loc, p), 2) - pow(h, 2));
	if (h > 0 && d < co->diameter / 2 && h < co->height)
		return (1);
	else
		return (-1);
}

int	is_in_co(t_obj_cone *co)
{
	double	h;
	double	d;

	h = v_inner_product(co->normal, v_multiply(co->loc, (-1)));
	d = sqrt(pow(v_size(co->loc), 2) - pow(h, 2));
	if (h > 0 && d < co->diameter / 2 && h < co->height)
		return (1);
	else
		return (-1);
}
