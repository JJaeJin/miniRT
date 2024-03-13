/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ambient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:35:19 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/13 21:01:31 by dongyeuk         ###   ########.fr       */
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
