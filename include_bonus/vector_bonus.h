/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:18:28 by jaejilee          #+#    #+#             */
/*   Updated: 2024/04/01 13:28:49 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_BONUS_H
# define VECTOR_BONUS_H

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef t_vector	t_point;

double		v_inner_product(t_vector v1, t_vector v2);
double		v_size(t_vector v);
t_vector	v_outer_product(t_vector v1, t_vector v2);
t_vector	v_add(t_vector v1, t_vector v2);
t_vector	v_sub(t_vector v1, t_vector v2);
double		*solve_quadratic(double a, double b, double c);
void		v_normalize(t_vector *v);
double		p_get_distance(t_point p1, t_point p2);
double		v_get_cos(t_vector p_to_l, t_vector n);
t_vector	p_get_vector(t_point start, t_point end);
t_vector	v_multiply(t_vector v, double num);
t_vector	rgb_get_normalmap_v(char *dst);

#endif