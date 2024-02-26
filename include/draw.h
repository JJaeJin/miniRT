/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:57:20 by jaejilee          #+#    #+#             */
/*   Updated: 2024/02/26 13:35:23 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "argument.h"

# define ON_DESTROY		17
# define ON_KEYBOARD	2
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
}	t_mlx;

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
void	draw_all(t_info info);
void	make_img(t_mlx *data, t_info info);
void	check_sphere(t_color *rgb, double *distance, t_vector v, t_info info);
void	check_plane(t_color *rgb, double *distance, t_vector v, t_info info);
void	check_cylinder(t_color *rgb, double *distance, t_vector v, t_info info);

#endif