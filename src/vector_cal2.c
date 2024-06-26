/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_cal2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:54:45 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/29 20:38:13 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"
#include <math.h>

// y = ax^2 + bx + c
double	*solve_quadratic(double a, double b, double c)
{
	double	*res;
	double	abs_d;
	double	d;

	d = pow(b, 2) - 4 * a * c;
	abs_d = fabs(d);
	if (abs_d < 0.00000001)
	{
		res = (double *)ft_calloc(2, sizeof(double));
		res[0] = (-1 * b) / (2 * a);
		res[1] = res[0];
	}
	else if (d < 0)
		return (NULL);
	else
	{
		res = (double *)ft_calloc(2, sizeof(double));
		res[0] = (-1 * b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
		res[1] = (-1 * b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	}
	return (res);
}

void	v_normalize(t_vector *v)
{
	double	size;

	size = v_size(*v);
	if (size == 0)
		return ;
	v->x /= size;
	v->y /= size;
	v->z /= size;
}

double	p_get_distance(t_point p1, t_point p2)
{
	double	res;

	res = 0;
	res += pow(p1.x - p2.x, 2);
	res += pow(p1.y - p2.y, 2);
	res += pow(p1.z - p2.z, 2);
	res = sqrt(res);
	return (res);
}

double	v_get_cos(t_vector p_to_l, t_vector n)
{
	return (v_inner_product(p_to_l, n) / (v_size(p_to_l) * v_size(n)));
}

t_vector	p_get_vector(t_point start, t_point end)
{
	t_vector	res;

	res.x = end.x - start.x;
	res.y = end.y - start.y;
	res.z = end.z - start.z;
	return (res);
}
