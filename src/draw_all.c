/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:31:44 by jaejilee          #+#    #+#             */
/*   Updated: 2024/02/26 13:33:58 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "mlx.h"
#include "draw.h"
#include <stdlib.h>

static void	init_mlx(t_mlx *data);
static int	close_exit(int keycode, t_mlx *data);
static int	key_hook(int keycode, t_mlx *data);

void	draw_all(t_info info)
{
	t_mlx	data;

	init_mlx(&data);
	make_img(&data, info);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, ON_DESTROY, 0, close_exit, &data);
	mlx_hook(data.win, ON_KEYBOARD, 0, key_hook, &data);
	mlx_loop(data.mlx);
}

static void	init_mlx(t_mlx *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, SCREEN_W, SCREEN_H, "miniRT");
	data->img = mlx_new_image(data->mlx, SCREEN_W, SCREEN_H);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, \
					&data->line_length, &data->endian);
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
	(void)data;
	if (keycode == KB_ESC)
		exit(0);
	return (0);
}
