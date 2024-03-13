/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:35:19 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/13 21:36:14 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "color.h"
#include "draw.h"

void	apply_ambient(t_color *c, t_ambient_lightning *amb)
{
	c->red *= amb->color.red * amb->ratio / 255;
	if (c->red > 255)
		c->red = 255;
	c->green *= amb->color.green * amb->ratio / 255;
	if (c->green > 255)
		c->green = 255;
	c->blue *= amb->color.blue * amb->ratio / 255;
	if (c->blue > 255)
		c->blue = 255;
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
