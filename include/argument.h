/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:17:36 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/13 16:52:37 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGUMENT_H
# define ARGUMENT_H

# include "vector.h"
# include "color.h"
# include <stdlib.h>

# define SUCCESS (0)
# define FAILURE (1)

typedef struct s_camera
{
	t_point		loc;
	t_vector	way;
	double		fov;
}	t_camera;

typedef struct s_ambient_lightning
{
	double	ratio;
	t_color	color;
}	t_ambient_lightning;

typedef struct s_light
{
	t_point			loc;
	double			ratio;
	t_color			color;
	struct s_light	*next;
}	t_light;

typedef struct s_obj_sphere
{
	t_point				center;
	double				diameter;
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
	double					height;
	double					diameter;
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
int		is_unsigned_double(char *s, double *f);
int		is_rgb(char *s, t_color *clr);
int		fail_free(void *p);

int		read_sp(t_obj *obj, char **all_info);
int		read_pl(t_obj *obj, char **all_info);
int		read_cy(t_obj *obj, char **all_info);
int		read_cam(t_info *info, char **all_info);
int		read_light(t_info *info, char **all_info);
int		read_amb(t_info *info, char **all_info);

void	convert_system(t_info *info);

void	check_sphere(t_color *rgb, double *distance, t_vector v, t_info info);
void	check_plane(t_color *rgb, double *distance, t_vector v, t_info info);
void	check_cylinder(t_color *rgb, double *distance, t_vector v, t_info info);
void	apply_ambient(t_color *c, t_ambient_lightning *amb);

/* funcs for cylinder */
void	get_p_bottom(t_vector v, t_point *p, t_obj_cylinder *cy);
void	get_p_side(t_vector v, t_point *p, t_obj_cylinder *cy);
void	get_p_side_others(t_vector v, t_point *p, t_obj_cylinder *cy);
double	get_height_diff(t_vector v_ray, t_obj_cylinder *cy);
double	get_d_between_lines(t_vector v_ray, t_obj_cylinder *cy);
t_point	get_p_center(t_obj_cylinder *cy, t_vector v);

#endif