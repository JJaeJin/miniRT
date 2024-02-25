/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:57:20 by jaejilee          #+#    #+#             */
/*   Updated: 2024/02/25 11:37:45 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "argument.h"

# define ON_DESTROY		17
# define ON_KEYBOARD	2
# define KB_ESC			53

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_mlx;

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
void	draw_all(t_info info);

#endif