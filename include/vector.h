/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:18:28 by jaejilee          #+#    #+#             */
/*   Updated: 2024/02/26 14:46:37 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef t_vector	t_point;

double		v_inner_product(t_vector v1, t_vector v2);
double		v_size(t_vector v);
t_vector	*v_outer_product(t_vector v1, t_vector v2);
t_vector	*v_add(t_vector v1, t_vector v2);
t_vector	*v_sub(t_vector v1, t_vector v2);
double		*solve_quadratic(double a, double b, double c);
t_point		*get_near_p(t_point cam, t_vector v, double *t);
void		v_normalize(t_vector *v);

#endif