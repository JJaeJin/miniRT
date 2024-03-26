/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:21:20 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/26 13:50:49 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "vector.h"
#include "argument.h"
#include "libft.h"
#include <math.h>
// #include <stdio.h>

static t_vector	get_3d_vector(int x, int y, t_info info);
static void		law_rodrigues(t_vector *res, t_vector cw, \
							t_vector normal, t_vector ndc_t);
static void		init_img_data(t_final_c *rgb, double *distance);

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	make_img(t_mlx *data, t_info info)
{
	int				x;
	int				y;
	t_final_c		rgb;
	double			distance;
	t_vector		v;

	x = -1;
	while (++x < SCREEN_W)
	{
		y = -1;
		while (++y < SCREEN_H)
		{
			// printf("\nx = %d, y = %d\n", x, y);
			init_img_data(&rgb, &distance);
			distance = 0;
			v = get_3d_vector(x, y, info);
			check_sphere(&rgb, &distance, v, info);
			check_plane(&rgb, &distance, v, info);
			check_cylinder(&rgb, &distance, v, info);
			check_cone(&rgb, &distance, v, info);
			if (distance != 0)
				apply_draw(rgb, data, x, y);
		}
	}
}

static t_vector	get_3d_vector(int x, int y, t_info info)
{
	t_vector	ndc_t;
	t_vector	res;
	t_vector	normal;
	t_vector	z;

	ndc_t.x = x - SCREEN_W / 2;
	ndc_t.y = y - SCREEN_H / 2;
	ndc_t.z = (SCREEN_W / 2) / tan(M_PI / 180 * (info.camera->fov / 2));
	z.x = 0;
	z.y = 0;
	z.z = 1;
	normal = v_outer_product(z, info.camera->way);
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
	t_vector	z;

	z.x = 0;
	z.y = 0;
	z.z = 1;
	cos_th = v_inner_product(z, cw) / (v_size(z) * v_size(cw));
	sin_th = sqrt(1 - pow(cos_th, 2));
	temp = v_outer_product(normal, ndc_t);
	res->x = cos_th * ndc_t.x + (1 - cos_th) * v_inner_product(normal, ndc_t) \
			* normal.x + sin_th * temp.x;
	res->y = cos_th * ndc_t.y + (1 - cos_th) * v_inner_product(normal, ndc_t) \
			* normal.y + sin_th * temp.y;
	res->z = cos_th * ndc_t.z + (1 - cos_th) * v_inner_product(normal, ndc_t) \
			* normal.z + sin_th * temp.z;
}

static void	init_img_data(t_final_c *rgb, double *distance)
{
	*distance = 0;
	rgb->color.red = 0;
	rgb->color.green = 0;
	rgb->color.blue = 0;
	rgb->ratio.red = 0;
	rgb->ratio.green = 0;
	rgb->ratio.blue = 0;
	rgb->specular.red = 0;
	rgb->specular.green = 0;
	rgb->specular.blue = 0;
}
