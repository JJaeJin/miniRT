/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:57:20 by jaejilee          #+#    #+#             */
/*   Updated: 2024/02/27 11:05:47 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "argument.h"

# define ON_DESTROY		17
# define ON_KEYBOARD	2
# define KB_DOWN		125
# define KB_UP			126
# define KB_ESC			53

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

#endif