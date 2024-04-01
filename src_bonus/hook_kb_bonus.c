/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_kb_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:05:28 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/04/01 13:58:46 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument_bonus.h"
#include "mlx.h"
#include "draw_bonus.h"
#include <stdlib.h>

static t_vector	get_outer_result_of_way(t_mlx *data);

void	clear_img(t_mlx *data)
{
	int		x;
	int		y;
	char	*dst;

	x = 0;
	while (x < SCREEN_W)
	{
		y = 0;
		while (y < SCREEN_H)
		{
			dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
			*(unsigned int *)dst = 0x000000;
			y++;
		}
		x++;
	}
}

void	apply_kb_plus_minus(int keycode, t_mlx *data)
{
	if (keycode == KB_PLUS && data->info->amb->ratio != 1)
	{
		data->info->amb->ratio += 0.1;
		if (data->info->amb->ratio > 1.0)
			data->info->amb->ratio = 1;
	}
	else if (keycode == KB_MINUS && data->info->amb->ratio != 0)
	{
		data->info->amb->ratio -= 0.1;
		if (data->info->amb->ratio < 0)
			data->info->amb->ratio = 0;
	}
}

void	apply_kb_w_s_q_e(int keycode, t_mlx *data)
{
	clear_img(data);
	if (keycode == KB_W)
	{
		data->info->camera->loc.x += data->info->camera->way.x * 10;
		data->info->camera->loc.y += data->info->camera->way.y * 10;
		data->info->camera->loc.z += data->info->camera->way.z * 10;
	}
	else if (keycode == KB_S)
	{
		data->info->camera->loc.x -= data->info->camera->way.x * 10;
		data->info->camera->loc.y -= data->info->camera->way.y * 10;
		data->info->camera->loc.z -= data->info->camera->way.z * 10;
	}
	else if (keycode == KB_Q)
		data->info->camera->loc.y += 10;
	else if (keycode == KB_E)
		data->info->camera->loc.y -= 10;
	convert_system(data->info);
}

void	apply_kb_a_d(int keycode, t_mlx *data)
{
	t_vector	tmp;

	tmp = get_outer_result_of_way(data);
	clear_img(data);
	if (keycode == KB_A)
	{
		data->info->camera->loc.x += tmp.x * 10;
		data->info->camera->loc.y += tmp.y * 10;
		data->info->camera->loc.z += tmp.z * 10;
	}
	else if (keycode == KB_D)
	{
		data->info->camera->loc.x -= tmp.x * 10;
		data->info->camera->loc.y -= tmp.y * 10;
		data->info->camera->loc.z -= tmp.z * 10;
	}
	else if (keycode == KB_C)
		data->info->checkerboard = (data->info->checkerboard + 1) % 2;
	else if (keycode == KB_B)
		data->info->bumpmap = (data->info->bumpmap + 1) % 2;
	convert_system(data->info);
}

static t_vector	get_outer_result_of_way(t_mlx *data)
{
	t_vector	tmp;

	tmp.x = 0;
	if (data->info->camera->way.y == 1)
	{
		tmp.y = 0;
		tmp.z = 1;
	}
	else
	{
		tmp.y = 1;
		tmp.z = 0;
	}
	tmp = v_outer_product(tmp, data->info->camera->way);
	return (tmp);
}
