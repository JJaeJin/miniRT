/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:57:20 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/24 09:48:58 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "argument.h"

# define ON_DESTROY		17
# define ON_KEYBOARD	2
# define KB_MINUS		27
# define KB_PLUS		24
# define KB_ESC			53
# define KB_W			13
# define KB_A			0
# define KB_S			1
# define KB_D			2
# define KB_Q			12
# define KB_E			14
# define KB_C			8

# define SCREEN_W		800
# define SCREEN_H		800

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	t_info	*info;
}	t_mlx;

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
void	draw_all(t_info info);
void	make_img(t_mlx *data, t_info info);

void	clear_img(t_mlx *data);
void	apply_kb_plus_minus(int keycode, t_mlx *data);
void	apply_kb_w_s_q_e(int keycode, t_mlx *data);
void	apply_kb_a_d(int keycode, t_mlx *data);

void	apply_draw(t_final_c rgb, t_mlx *data, int x, int y);

#endif