/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_cal3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:54:45 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/28 17:06:01 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "vector.h"
#include "libft.h"
#include <math.h>
#include <color.h>

t_vector	v_multiply(t_vector v, double num)
{
	v.x *= num;
	v.y *= num;
	v.z *= num;
	return (v);
}

t_vector	rgb_get_normalmap_v(char *dst)
{
	t_vector	res;

	res.x = ((*(unsigned int *)dst >> 16) & 0xFF);
	res.y = ((*(unsigned int *)dst >> 8) & 0xFF);
	res.z = (*(unsigned int *)dst & 0xFF);
	res.x = res.x / 255 * 2 - 1;
	res.y = res.y / 255 * 2 - 1;
	res.z = res.z / 255 * 2 - 1;
	return (res);
}

int	check_specular(t_light *l, t_point p, t_vector n)
{
	t_vector	specular;
	t_vector	p_to_l;

	p_to_l = p_get_vector(p, l->loc);
	n = v_multiply(n, v_inner_product(p_to_l, n));
	specular = v_add(n, v_sub(n, p_to_l));
	if (v_get_cos(specular, v_multiply(p, -1)) > 0)
		return (TRUE);
	else
		return (FALSE);
}
