/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:35:45 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/24 13:01:29 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

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