/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:35:45 by jaejilee          #+#    #+#             */
/*   Updated: 2024/04/01 13:29:46 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_BONUS_H
# define COLOR_BONUS_H

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
	t_color	specular;
}	t_final_c;

t_color	get_complementary_color(t_color c);

#endif