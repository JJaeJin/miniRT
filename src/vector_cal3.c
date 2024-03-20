/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_cal3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:54:45 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/19 13:33:51 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"
#include <math.h>

t_vector	v_multiply(t_vector v, double num)
{
	v.x *= num;
	v.y *= num;
	v.z *= num;
	return (v);
}
