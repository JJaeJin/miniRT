/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_obstacles_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:46:14 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/31 10:49:29 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "vector.h"
#include <math.h>

int	is_in_sp(t_point p, t_obj_sphere *sp)
{
	if (p_get_distance(p, sp->center) <= sp->diameter / 2)
		return (1);
	return (-1);
}
