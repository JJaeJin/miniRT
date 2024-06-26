/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:17:36 by jaejilee          #+#    #+#             */
/*   Updated: 2024/04/01 13:30:11 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGUMENT_BONUS_H
# define ARGUMENT_BONUS_H

# include "vector_bonus.h"
# include "color_bonus.h"
# include <stdlib.h>

# define SUCCESS		(0)
# define FAILURE		(1)

# define OBS_EXIST		(1)
# define OBS_NOT_EXIST	(0)

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
	t_vector			temp_normal;
	struct s_obj_sphere	*next;
}	t_obj_sphere;

typedef struct s_obj_plane
{
	t_point				loc;
	t_vector			normal;
	t_color				color;
	t_vector			temp_normal;
	struct s_obj_plane	*next;
}	t_obj_plane;

typedef struct s_obj_cylinder
{
	t_point					loc;
	t_vector				normal;
	double					height;
	double					diameter;
	t_color					color;
	t_vector				cam;
	t_vector				temp_normal;
	struct s_obj_cylinder	*next;
}	t_obj_cylinder;

typedef struct s_obj_cone
{
	t_point				loc;
	t_vector			normal;
	double				height;
	double				diameter;
	t_color				color;
	struct s_obj_cone	*next;
}	t_obj_cone;

typedef struct s_obj
{
	t_obj_cylinder	*cy;
	t_obj_plane		*pl;
	t_obj_sphere	*sp;
	t_obj_cone		*co;
}	t_obj;

typedef struct s_img
{
	void	*img;
	void	*img_addr;
	int		img_size[2];
	int		img_bpp;
	int		img_line_length;
	int		img_endian;
}	t_img;

typedef struct s_info
{
	t_camera			*camera;
	t_ambient_lightning	*amb;
	t_light				*lights;
	t_obj				*objs;
	int					checkerboard;
	int					bumpmap;

	t_img				pl_img;
	t_img				pl_normalmap;

	void				*sp_img;
	void				*sp_normal_map;
}	t_info;

void		init_obj(t_info *info);
int			parse_all(t_info *info, char *file);
int			is_vector(char *s, t_vector *v);
int			is_unsigned_double(char *s, double *f);
int			is_rgb(char *s, t_color *clr);
int			fail_free(void *p, char **ptr);

int			read_sp(t_obj *obj, char **all_info);
int			read_pl(t_obj *obj, char **all_info);
int			read_cy(t_obj *obj, char **all_info);
int			read_co(t_obj *obj, char **all_info);
int			read_cam(t_info *info, char **all_info);
int			read_light(t_info *info, char **all_info);
int			read_amb(t_info *info, char **all_info);

void		convert_system(t_info *info);

int			get_sign(double n);

/* draw objects */
void		check_sphere(t_final_c *rgb, double *distance, \
							t_vector v, t_info info);
void		check_plane(t_final_c *rgb, double *distance, \
							t_vector v, t_info info);
void		check_cylinder(t_final_c *rgb, double *distance, \
							t_vector v, t_info info);
void		apply_ambient(t_final_c *rgb, t_ambient_lightning *amb);
void		apply_diffuse(t_color *ratio, t_light *l, double cos_th);
void		apply_specular(t_final_c *rgb, t_light *l, t_point p, t_vector n);

/* funcs for cylinder */
void		get_p_bottom(t_vector v, t_point *p, t_obj_cylinder *cy);
void		get_p_side(t_vector v, t_point *p, t_obj_cylinder *cy);
void		get_p_side_others(t_vector v, t_point *p, \
							t_obj_cylinder *cy, t_vector *move);
double		get_height_diff(t_vector v_ray, t_obj_cylinder *cy);
double		get_d_between_lines(t_vector v_ray, t_obj_cylinder *cy);
t_point		get_p_center(t_obj_cylinder *cy, t_vector v);
int			p_is_in_cy(t_point p, t_obj_cylinder *cy);
double		get_contact_t(t_vector temp, t_vector v_ray, t_point p_on_cy);

/* funcs for cone */
void		check_cone(t_final_c *rgb, double *distance, \
								t_vector v, t_info info);
int			co_check_p_side(double d_res, double *distance, double *diff);
void		co_get_p_bottom(t_vector v, t_point *p, t_obj_cone *co);
int			check_obs_cone(t_point l, t_point p, t_obj_cone *co, void *obj);
double		*co_get_diff_set_p_side(t_point *p, t_vector v, t_obj_cone *co);
double		co_get_distance(t_point *p, t_obj_cone *co, \
								t_vector cam, t_vector v);
int			p_is_in_co(t_point p, t_obj_cone *co);
int			is_in_co(t_obj_cone *co);

/* get_obj_normal */
t_vector	get_sphere_normal(t_obj_sphere *sp, t_point p);
t_vector	get_cylinder_normal(t_obj_cylinder *cy, t_point p);
t_vector	get_cone_normal(t_obj_cone *co, t_point p);

/* check_obstacles */
int			check_obstacles(t_point l, t_point p, t_info info, void *obj);
int			check_obs_sphere(t_point l, t_point p, t_obj_sphere *sp, void *obj);
int			check_obs_plane(t_point l, t_point p, t_obj_plane *pl, void *obj);
int			check_obs_cylinder(t_point l, t_point p, \
								t_obj_cylinder *cy, void *obj);
int			check_specular(t_light *l, t_point p, t_vector n);
int			is_in_cy(t_obj_cylinder *cy);
int			is_in_sp(t_point p, t_obj_sphere *sp);

/* get_checkerboard_color */
void		get_cb_color_sp(t_obj_sphere *sp, t_info info, \
								t_point p, t_color *c);

/* get_img_color */
t_color		get_img_color(t_img img, t_point p);
t_vector	get_img_vector(t_img img, t_point p, t_vector n);

/* leak_funcs */
int			free_double_char_pointer_rt_int(char **ptr, int rt_value);

#endif