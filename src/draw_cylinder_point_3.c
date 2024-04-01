/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder_point_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:26:04 by jaejilee          #+#    #+#             */
/*   Updated: 2024/04/01 14:28:14 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "draw.h"
#include "vector.h"
#include "libft.h"
#include <math.h>

double	get_contact_t(t_vector temp, t_vector v_ray, t_point p_on_cy)
{
	double	t;

	if (v_ray.x == 0 && v_ray.y == 0)
		t = (temp.y * p_on_cy.z - temp.z * p_on_cy.y) / \
			(v_ray.z * temp.y - v_ray.y * temp.z);
	else
		t = (temp.y * p_on_cy.x - temp.x * p_on_cy.y) / \
			(v_ray.x * temp.y - v_ray.y * temp.x);
	return (t);
}
