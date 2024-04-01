/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_cal1_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:25:35 by jaejilee          #+#    #+#             */
/*   Updated: 2024/04/01 13:57:47 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_bonus.h"
#include "libft.h"
#include <math.h>

double	v_inner_product(t_vector v1, t_vector v2)
{
	double	res;

	res = 0;
	res += v1.x * v2.x;
	res += v1.y * v2.y;
	res += v1.z * v2.z;
	return (res);
}

t_vector	v_outer_product(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

t_vector	v_add(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_vector	v_sub(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

double	v_size(t_vector v)
{
	double	res;

	res = 0;
	res += pow(v.x, 2);
	res += pow(v.y, 2);
	res += pow(v.z, 2);
	res = sqrt(res);
	return (res);
}
