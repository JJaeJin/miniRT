/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:35:19 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/15 20:33:21 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "color.h"
#include "vector.h"
#include "draw.h"

void	apply_ambient(t_final_c *rgb, t_ambient_lightning *amb)
{
	rgb->ratio.red = rgb->color.red * amb->color.red * amb->ratio / 255;
	rgb->ratio.green = rgb->color.green * amb->color.green * amb->ratio / 255;
	rgb->ratio.blue = rgb->color.blue * amb->color.blue * amb->ratio / 255;
}

void	apply_diffuse(t_color *c, t_light *diff, double cos_th)
{
	c->red *= diff->color.red * diff->ratio * cos_th / 255;
	if (c->red > 255)
		c->red = 255;
	c->green *= diff->color.green * diff->ratio * cos_th / 255;
	if (c->green > 255)
		c->green = 255;
	c->blue *= diff->color.blue * diff->ratio * cos_th / 255;
	if (c->blue > 255)
		c->blue = 255;
}

void	apply_draw(t_final_c rgb, t_mlx *data, int x, int y)
{
	t_color	res;

	res.red = rgb.color.red * rgb.ratio.red;
	if (res.red > 255)
		res.red = 255;
	res.green = rgb.color.green * rgb.ratio.green;
	if (res.green > 255)
		res.green = 255;
	res.blue = rgb.color.blue * rgb.ratio.blue;
	if (res.blue > 255)
		res.blue = 255;
	my_mlx_pixel_put(data, x, y, \
					(int)res.red << 16 | (int)res.green << 8 | (int)res.blue);
}
