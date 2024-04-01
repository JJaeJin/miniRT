/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_img_color_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:25:11 by jaejilee          #+#    #+#             */
/*   Updated: 2024/04/01 13:54:58 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument_bonus.h"
#include <math.h>

static t_vector	get_bump_vector(t_vector n, t_vector v);

t_color	get_img_color(t_img img, t_point p)
{
	t_color	res;
	char	*dst;

	while (p.x < 0)
		p.x += img.img_size[0];
	while (p.y < 0)
		p.y += img.img_size[1];
	while (p.x > img.img_size[0])
		p.x -= img.img_size[0];
	while (p.y > img.img_size[1])
		p.y -= img.img_size[1];
	dst = img.img_addr + ((int)p.y * img.img_line_length + \
			(int)p.x * (img.img_bpp / 8));
	res.red = (*(unsigned int *)dst >> 16) & 0xFF;
	res.green = (*(unsigned int *)dst >> 8) & 0xFF;
	res.blue = *(unsigned int *)dst & 0xFF;
	return (res);
}

t_vector	get_img_vector(t_img img, t_point p, t_vector n)
{
	t_vector	temp;
	char		*dst;

	while (p.x < 0)
		p.x += img.img_size[0];
	while (p.y < 0)
		p.y += img.img_size[1];
	while (p.x > img.img_size[0])
		p.x -= img.img_size[0];
	while (p.y > img.img_size[1])
		p.y -= img.img_size[1];
	dst = img.img_addr + ((int)p.y * img.img_line_length + \
			(int)p.x * (img.img_bpp / 8));
	temp = rgb_get_normalmap_v(dst);
	return (get_bump_vector(n, temp));
}

static t_vector	get_bump_vector(t_vector n, t_vector v)
{
	t_vector	res;
	t_vector	v_z;
	double		cos_th;
	double		sin_th;
	t_vector	temp;

	v_z.x = 0;
	v_z.y = 0;
	v_z.z = 1;
	temp = v_outer_product(v_z, n);
	v_normalize(&temp);
	v_normalize(&n);
	cos_th = v_get_cos(v_z, n);
	sin_th = sqrt(1 - pow(cos_th, 2));
	res = v_add(v_add(v_multiply(v, cos_th), v_multiply(n, (1 - cos_th) \
		* v_inner_product(v, temp))), \
		v_multiply(v_outer_product(temp, v), sin_th));
	return (res);
}
