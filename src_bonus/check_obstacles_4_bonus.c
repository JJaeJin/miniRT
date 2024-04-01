/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_obstacles_4_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:46:14 by jaejilee          #+#    #+#             */
/*   Updated: 2024/04/01 13:54:58 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument_bonus.h"
#include "vector_bonus.h"
#include <math.h>

int	is_in_sp(t_point p, t_obj_sphere *sp)
{
	if (p_get_distance(p, sp->center) <= sp->diameter / 2)
		return (1);
	return (-1);
}
