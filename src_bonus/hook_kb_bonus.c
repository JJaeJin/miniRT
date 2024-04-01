/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_kb_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:05:28 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/04/01 14:16:15 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument_bonus.h"
#include "mlx.h"
#include "draw_bonus.h"
#include <stdlib.h>

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

void	apply_kb_c_b(int keycode, t_mlx *data)
{
	clear_img(data);
	if (keycode == KB_C)
		data->info->checkerboard = (data->info->checkerboard + 1) % 2;
	else if (keycode == KB_B)
		data->info->bumpmap = (data->info->bumpmap + 1) % 2;
}
