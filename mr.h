/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:23:14 by jaejilee          #+#    #+#             */
/*   Updated: 2024/02/17 12:47:01 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MR_H
# define MR_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"

typedef struct s_vector
{
	int	x;
	int	y;
	int	z;
}	t_vector;

typedef t_vector t_point;

typedef struct s_camera
{
	t_point		loc;
	t_vector	way;
	int			fov;
}	t_camera;

typedef struct s_ambient_lightning
{
	float	ratio;
	int		color;
}	t_ambient_lightning;

typedef struct s_light
{
	t_point			loc;
	float			ratio;
	int				color;
	struct s_light	*next;
}	t_light;

typedef struct s_obj_sphere
{
	t_point				center;
	int					diameter;
	int					color;
	struct s_obj_sphere	*next;
}	t_obj_sphere;

typedef struct s_obj_plane
{
	t_point				loc;
	t_vector			normal;
	int					color;
	struct s_obj_plane	*next;
}	t_obj_plane;

typedef struct s_obj_cylinder
{
	t_point					loc;
	t_vector				normal;
	int						height;
	int						diameter;
	int						color;
	struct s_obj_cylinder	*next;
}	t_obj_cylinder;

typedef struct s_obj
{
	t_obj_cylinder	*cy;
	t_obj_plane		*pl;
	t_obj_sphere	*sp;
}	t_obj;

#endif