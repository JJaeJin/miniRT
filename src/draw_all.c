/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:31:44 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/27 12:54:23 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "mlx.h"
#include "draw.h"
#include <stdlib.h>

static void	init_mlx(t_mlx *data, t_info *info);
static int	close_exit(int keycode, t_mlx *data);
static int	key_hook(int keycode, t_mlx *data);

void	draw_all(t_info info)
{
	t_mlx	data;

	init_mlx(&data, &info);
	data.info = &info;
	make_img(&data, *data.info);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, ON_DESTROY, 0, close_exit, &data);
	mlx_hook(data.win, ON_KEYBOARD, 0, key_hook, &data);
	mlx_loop(data.mlx);
}

static void	init_mlx(t_mlx *data, t_info *info)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, SCREEN_W, SCREEN_H, "miniRT");
	data->img = mlx_new_image(data->mlx, SCREEN_W, SCREEN_H);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, \
					&data->line_length, &data->endian);
	info->pl_img.img = mlx_xpm_file_to_image(data->mlx, \
			"./map/pl_brick_pattern_1.xpm", info->pl_img.img_size, \
			info->pl_img.img_size + 1);
	info->pl_img.img_addr = mlx_get_data_addr(info->pl_img.img, \
			&info->pl_img.img_bpp, &info->pl_img.img_line_length, \
			&info->pl_img.img_endian);
	info->pl_normalmap.img = mlx_xpm_file_to_image(data->mlx, \
			"./map/pl_brick_normalmap_1.xpm", info->pl_normalmap.img_size, \
			info->pl_normalmap.img_size + 1);
	info->pl_normalmap.img_addr = mlx_get_data_addr(info->pl_normalmap.img, \
			&info->pl_normalmap.img_bpp, &info->pl_normalmap.img_line_length, \
			&info->pl_normalmap.img_endian);
}

static int	close_exit(int keycode, t_mlx *data)
{
	keycode++;
	(void)data;
	exit(0);
	return (0);
}

static int	key_hook(int keycode, t_mlx *data)
{
	if (keycode == KB_ESC)
		exit(0);
	else if ((keycode == KB_PLUS && data->info->amb->ratio != 1)
		|| (keycode == KB_MINUS && data->info->amb->ratio != 0))
		apply_kb_plus_minus(keycode, data);
	else if (keycode == KB_W || keycode == KB_S || keycode == KB_Q
		|| keycode == KB_E)
		apply_kb_w_s_q_e(keycode, data);
	else if (keycode == KB_A || keycode == KB_D || keycode == KB_C \
			|| keycode == KB_B)
		apply_kb_a_d(keycode, data);
	else
		return (1);
	make_img(data, *data->info);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
