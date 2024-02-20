/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:17:36 by jaejilee          #+#    #+#             */
/*   Updated: 2024/02/20 10:33:22 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGUMENT_H
# define ARGUMENT_H

# include "vector.h"
# include "color.h"

# define SUCCESS 0
# define FAILURE 1

typedef struct s_camera
{
	t_point		loc;
	t_vector	way;
	int			fov;
}	t_camera;

typedef struct s_ambient_lightning
{
	float	ratio;
	t_color	color;
}	t_ambient_lightning;

typedef struct s_light
{
	t_point			loc;
	float			ratio;
	t_color			color;
	struct s_light	*next;
}	t_light;

typedef struct s_obj_sphere
{
	t_point				center;
	int					diameter;
	t_color				color;
	struct s_obj_sphere	*next;
}	t_obj_sphere;

typedef struct s_obj_plane
{
	t_point				loc;
	t_vector			normal;
	t_color				color;
	struct s_obj_plane	*next;
}	t_obj_plane;

typedef struct s_obj_cylinder
{
	t_point					loc;
	t_vector				normal;
	int						height;
	int						diameter;
	t_color					color;
	struct s_obj_cylinder	*next;
}	t_obj_cylinder;

typedef struct s_obj
{
	t_obj_cylinder	*cy;
	t_obj_plane		*pl;
	t_obj_sphere	*sp;
}	t_obj;

typedef struct s_info
{
	t_camera			*camera;
	t_ambient_lightning	*amb;
	t_light				*lights;
	t_obj				*objs;
}	t_info;

void	init_obj(t_info *info);
int		parse_all(t_info *info, char *file);
int		is_vector(char *s, t_vector *v);
int		is_double(char *s, double *f);
int		is_unsigned_double(char *s, double *f);
int		is_rgb(char *s, t_vector *v);
int		fail_free(void *p);

#endif