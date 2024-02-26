/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:21:20 by jaejilee          #+#    #+#             */
/*   Updated: 2024/02/26 15:25:46 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "vector.h"
#include "argument.h"
#include "libft.h"
#include <math.h>
#include <stdio.h>

static t_vector	*get_3d_vector(int x, int y, t_info info);
static void		law_rodrigues(t_vector *res, t_vector cw, \
							t_vector normal, t_vector ndc_t);

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
	double		disance;
	t_vector	*v;

	x = 0;
	while (x < SCREEN_W)
	{
		y = 0;
		while (y < SCREEN_H)
		{
			v = get_3d_vector(x, y, info);
			printf("vector = (%f, %f, %f)\n", v->x, v->y, v->z);
			check_sphere(&rgb, &disance, *v, info);
			check_plane(&rgb, &disance, *v, info);
			check_cylinder(&rgb, &disance, *v, info);
			my_mlx_pixel_put(data, x, y, 0xFFFFFF);
			free(v);
			y++;
		}
		x++;
	}
	disance = 0;
}

static t_vector	*get_3d_vector(int x, int y, t_info info)
{
	t_vector	ndc_t;
	t_vector	*res;
	t_vector	*normal;

	ndc_t.x = x - SCREEN_W / 2;
	ndc_t.y = y - SCREEN_H / 2;
	ndc_t.z = (SCREEN_W / 2) / tan(M_PI / 180 * (info.camera->fov / 2));
	res = (t_vector *)ft_calloc(1, sizeof(t_vector));
	normal = v_outer_product(ndc_t, info.camera->way);
	v_normalize(normal);
	law_rodrigues(res, info.camera->way, *normal, ndc_t);
	free(normal);
	return (res);
}

static void	law_rodrigues(t_vector *res, t_vector cw, \
							t_vector normal, t_vector ndc_t)
{
	t_vector	*temp;
	double		cos_th;
	double		sin_th;

	cos_th = v_inner_product(ndc_t, cw) \
				/ (v_size(ndc_t) * v_size(cw));
	sin_th = sqrt(1 - pow(cos_th, 2));
	temp = v_outer_product(normal, cw);
	res->x = cos_th * cw.x + sin_th * temp->x;
	res->y = cos_th * cw.y + sin_th * temp->y;
	res->z = cos_th * cw.z + sin_th * temp->z;
	free(temp);
}
