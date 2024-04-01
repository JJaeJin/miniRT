/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_checkerboard_color_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 10:10:49 by jaejilee          #+#    #+#             */
/*   Updated: 2024/04/01 13:54:58 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument_bonus.h"
#include "vector_bonus.h"
#include <math.h>

static t_point	get_cs_sp(t_point p);

void	get_cb_color_sp(t_obj_sphere *sp, t_info info, t_point p, t_color *c)
{
	t_point	p_converted;
	int		d;
	double	sign;
	t_color	t_c;

	t_c = sp->color;
	p_converted = get_cs_sp(v_sub(p, sp->center));
	if (info.bumpmap == 1)
	{
		t_c = get_img_color(info.pl_img, p_converted);
		sp->temp_normal = get_img_vector(info.pl_normalmap, \
				p_converted, sp->temp_normal);
	}
	if (info.checkerboard == 0)
	{
		*c = t_c;
		return ;
	}
	d = (abs((int)(p_converted.x / 100)) + \
		abs((int)(p_converted.y / 100))) % 2;
	sign = get_sign(p_converted.x) * get_sign(p_converted.y);
	if ((sign < 0 && d == 1) || (sign >= 0 && d == 0))
		*c = t_c;
	else
		*c = get_complementary_color(t_c);
}

static t_point	get_cs_sp(t_point p)
{
	t_point		res;
	t_vector	temp;
	t_vector	v_x;

	v_x.x = 0;
	v_x.y = 0;
	v_x.z = 1;
	temp = p;
	temp.y = 0;
	if (p.x < 0)
		res.x = acos(v_get_cos(v_x, temp));
	else
		res.x = -acos(v_get_cos(v_x, temp));
	if (p.y == 0)
		res.y = 0;
	else if (p.y < 0)
		res.y = acos(v_get_cos(temp, p));
	else
		res.y = -acos(v_get_cos(temp, p));
	return (v_multiply(res, (2000 / M_PI)));
}

int	get_sign(double n)
{
	if (n < 0)
		return (-1);
	else if (n == 0)
		return (0);
	else
		return (1);
}
