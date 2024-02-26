/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:07:38 by jaejilee          #+#    #+#             */
/*   Updated: 2024/02/26 17:36:26 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"

static void	convert_camera(t_camera *c);
static void	convert_lights(t_light *l, t_point mod);
static void	convert_sp_pl(t_obj *obj, t_point mod);
static void	convert_cy(t_obj *obj, t_point mod);

void	convert_system(t_info *info)
{
	t_point	mod;

	mod.x = info->camera->loc.x;
	mod.y = info->camera->loc.y;
	mod.z = info->camera->loc.z;
	convert_camera(info->camera);
	convert_lights(info->lights, mod);
	convert_sp_pl(info->objs, mod);
	convert_cy(info->objs, mod);
}

static void	convert_camera(t_camera *c)
{
	c->loc.x = 0;
	c->loc.y = 0;
	c->loc.z = 0;
}

static void	convert_lights(t_light *l, t_point mod)
{
	t_light	*temp;

	temp = l;
	while (temp != NULL)
	{
		temp->loc.x -= mod.x;
		temp->loc.y -= mod.y;
		temp->loc.z -= mod.z;
		temp = temp->next;
	}
}

static void	convert_sp_pl(t_obj *obj, t_point mod)
{
	t_obj_sphere	*temp_sp;
	t_obj_plane		*temp_pl;

	temp_sp = obj->sp;
	while (temp_sp != NULL)
	{
		temp_sp->center.x -= mod.x;
		temp_sp->center.y -= mod.y;
		temp_sp->center.z -= mod.z;
		temp_sp = temp_sp->next;
	}
	temp_pl = obj->pl;
	while (temp_pl != NULL)
	{
		temp_pl->loc.x -= mod.x;
		temp_pl->loc.y -= mod.y;
		temp_pl->loc.z -= mod.z;
		temp_pl = temp_pl->next;
	}
}

static void	convert_cy(t_obj *obj, t_point mod)
{
	t_obj_cylinder	*temp_cy;

	temp_cy = obj->cy;
	while (temp_cy != NULL)
	{
		temp_cy->loc.x -= mod.x;
		temp_cy->loc.y -= mod.y;
		temp_cy->loc.z -= mod.z;
		temp_cy = temp_cy->next;
	}
}
