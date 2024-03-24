/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:35:19 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/24 13:02:48 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "color.h"
#include "vector.h"
#include "draw.h"
#include <math.h>

void	apply_ambient(t_final_c *rgb, t_ambient_lightning *amb)
{
	rgb->ratio.red = rgb->color.red * amb->color.red * amb->ratio / 255;
	rgb->ratio.green = rgb->color.green * amb->color.green * amb->ratio / 255;
	rgb->ratio.blue = rgb->color.blue * amb->color.blue * amb->ratio / 255;
}

void	apply_diffuse(t_color *ratio, t_light *l, double cos_th)
{
	ratio->red += l->color.red * l->ratio * cos_th / 255;
	ratio->green += l->color.green * l->ratio * cos_th / 255;
	ratio->blue += l->color.blue * l->ratio * cos_th / 255;
}

void	apply_specular(t_final_c *rgb, t_light *l, t_point p, t_vector n)
{
	t_vector	specular;
	t_vector	p_to_l;
	double		cos_th;

	p_to_l = p_get_vector(p, l->loc);
	n = v_multiply(n, v_inner_product(p_to_l, n));
	specular = v_add(n, v_sub(n, p_to_l));
	cos_th = v_get_cos(specular, v_multiply(p, -1));
	if (cos_th > 0)
	{
		rgb->specular.red += l->color.red * l->ratio * pow(cos_th, 25);
		rgb->specular.green += l->color.green * l->ratio * pow(cos_th, 25);
		rgb->specular.blue += l->color.blue * l->ratio * pow(cos_th, 25);
	}
}

void	apply_draw(t_final_c rgb, t_mlx *data, int x, int y)
{
	t_color	res;

	res.red = 0;
	res.green = 0;
	res.blue = 0;
	res.red = rgb.color.red * rgb.ratio.red;
	res.red += rgb.specular.red;
	if (res.red > 255)
		res.red = 255;
	res.green = rgb.color.green * rgb.ratio.green;
	res.green += rgb.specular.green;
	if (res.green > 255)
		res.green = 255;
	res.blue = rgb.color.blue * rgb.ratio.blue;
	res.blue += rgb.specular.blue;
	if (res.blue > 255)
		res.blue = 255;
	my_mlx_pixel_put(data, x, y, \
					(int)res.red << 16 | (int)res.green << 8 | (int)res.blue);
}

t_color	get_complementary_color(t_color c)
{
	t_color	res;

	res.red = fabs(255 - c.red);
	res.green = fabs(255 - c.green);
	res.blue = fabs(255 - c.blue);
	return (res);
}
