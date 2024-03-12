/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:21:20 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/12 14:25:42 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "vector.h"
#include "argument.h"
#include "libft.h"
#include <math.h>
#include <stdio.h>

static t_vector	get_3d_vector(int x, int y, t_info info);
static void		law_rodrigues(t_vector *res, t_vector cw, \
							t_vector normal, t_vector ndc_t);
static void		init_img_data(t_color *rgb, double *distance);

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	make_img(t_mlx *data, t_info info)
{
	int			x;
	int			y;
	t_color		rgb;
	double		distance;
	t_vector	v;

	x = -1;
	while (++x < SCREEN_W)
	{
		y = -1;
		while (++y < SCREEN_H)
		{
			init_img_data(&rgb, &distance);
			v = get_3d_vector(x, y, info);
			check_sphere(&rgb, &distance, v, info);
			check_plane(&rgb, &distance, v, info);
			check_cylinder(&rgb, &distance, v, info);
			if (distance != 0)
			{
				apply_ambient(&rgb, info.amb);
				my_mlx_pixel_put(data, x, y, ((int)rgb.red << 16) \
								| ((int)rgb.green << 8) | (int)rgb.blue);
			}
		}
	}
}

static t_vector	get_3d_vector(int x, int y, t_info info)
{
	t_vector	ndc_t;
	t_vector	res;
	t_vector	normal;

	ndc_t.x = x - SCREEN_W / 2;
	ndc_t.y = y - SCREEN_H / 2;
	ndc_t.z = (SCREEN_W / 2) / tan(M_PI / 180 * (info.camera->fov / 2));
	normal = v_outer_product(ndc_t, info.camera->way);
	v_normalize(&normal);
	law_rodrigues(&res, info.camera->way, normal, ndc_t);
	v_normalize(&res);
	return (res);
}

static void	law_rodrigues(t_vector *res, t_vector cw, \
							t_vector normal, t_vector ndc_t)
{
	t_vector	temp;
	double		cos_th;
	double		sin_th;

	cos_th = v_inner_product(ndc_t, cw) \
				/ (v_size(ndc_t) * v_size(cw));
	sin_th = sqrt(1 - pow(cos_th, 2));
	temp = v_outer_product(normal, cw);
	res->x = cos_th * cw.x + sin_th * temp.x;
	res->y = cos_th * cw.y + sin_th * temp.y;
	res->z = cos_th * cw.z + sin_th * temp.z;
}

static void	init_img_data(t_color *rgb, double *distance)
{
	*distance = 0;
	rgb->red = 0;
	rgb->blue = 0;
	rgb->green = 0;
}
