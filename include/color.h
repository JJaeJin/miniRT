/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:35:45 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/15 11:51:54 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "argument.h"
# include "vector.h"
# include "draw.h"

typedef struct s_color
{
	double	red;
	double	green;
	double	blue;
	double	brightness;
}	t_color;

typedef struct s_final_c
{
	t_color	ratio;
	t_color	color;
}	t_final_c;

void	add_lights(t_final_c *rgb, t_point p, t_vector n, t_info info);
void	apply_draw(t_final_c rgb, t_mlx *data, int x, int y);

#endif