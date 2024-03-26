/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_checkerboard_color_1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 10:10:49 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/26 09:48:54 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "vector.h"
#include <math.h>

static t_point	get_cs_pl(t_vector pl, t_point p, t_vector v_z);
static t_point	get_cs_sp(t_point p);

void	get_cb_color_sp(t_obj_sphere *sp, t_info info, t_point p, t_color *c)
{
	t_point	p_converted;
	int		d;
	double	sign;

	if (info.checkerboard == 0)
	{
		*c = sp->color;
		return ;
	}
	p = v_sub(p, sp->center);
	p_converted = get_cs_sp(p);
	d = (abs((int)(p_converted.x / (M_PI / 10))) + \
		abs((int)(p_converted.y / (M_PI / 10)))) % 2;
	sign = get_sign(p_converted.x) * get_sign(p_converted.y);
	if ((sign < 0 && d == 1) || (sign >= 0 && d == 0))
		*c = sp->color;
	else
		*c = get_complementary_color(sp->color);
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
	return (res);
}

void	get_cb_color_pl(t_obj_plane *pl, t_info info, t_point p, t_color *c)
{
	t_vector	v_z;
	t_point		p_converted;
	int			d;
	double		sign;

	if (info.checkerboard == 0)
	{
		*c = pl->color;
		return ;
	}
	v_z.x = 0;
	v_z.y = 0;
	v_z.z = 1;
	p = v_sub(p, pl->loc);
	p_converted = get_cs_pl(pl->normal, p, v_z);
	d = (abs((int)p_converted.x / 30) + abs((int)p_converted.y / 30)) % 2;
	sign = get_sign(p_converted.x) * get_sign(p_converted.y);
	if ((sign > 0 && d == 0) || (sign <= 0 && d == 1))
		*c = pl->color;
	else
		*c = get_complementary_color(pl->color);
}

static t_point	get_cs_pl(t_vector pl, t_point p, t_vector v_z)
{
	t_vector	n;
	t_point		res;
	double		cos_th;
	double		sin_th;

	n = v_outer_product(v_z, pl);
	if (v_size(n) == 0)
		res = v_sub(p, pl);
	else
	{
		v_normalize(&n);
		cos_th = v_get_cos(v_z, n);
		sin_th = sqrt(1 - pow(cos_th, 2));
		res = v_add(v_add(v_multiply(p, cos_th), v_multiply(n, (1 - cos_th) \
			* v_inner_product(p, n))), \
			v_multiply(v_outer_product(n, p), sin_th));
	}
	return (res);
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
