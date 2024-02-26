/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_cal2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:54:45 by jaejilee          #+#    #+#             */
/*   Updated: 2024/02/26 14:45:53 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"
#include <math.h>

t_point	*get_near_p(t_point cam, t_vector v, double *t)
{
	t_point	*res;
	int		small_idx;

	res = (t_point *)ft_calloc(1, sizeof(t_point));
	if (sizeof(t) == sizeof(double))
		small_idx = 0;
	else
	{
		if (t[1] < 0)
		{
			free(res);
			return (NULL);
		}
		else if (t[0] < 0)
			small_idx = 1;
		else
			small_idx = 0;
	}
	res->x = cam.x + t[small_idx] * v.x;
	res->y = cam.y + t[small_idx] * v.y;
	res->z = cam.z + t[small_idx] * v.z;
	return (res);
}

// y = ax^2 + bx + c
double	*solve_quadratic(double a, double b, double c)
{
	double	*res;

	if (pow(b, 2) - 4 * a * c == 0)
	{
		res = (double *)ft_calloc(1, sizeof(double));
		res[0] = (-1 * b) / (2 * a);
	}
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
	v->x /= size;
	v->y /= size;
	v->z /= size;
}
