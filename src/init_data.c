/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:48:35 by jaejilee          #+#    #+#             */
/*   Updated: 2024/02/17 17:52:38 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"

void	init_obj(t_info *info)
{
	info->camera = NULL;
	info->amb = NULL;
	info->lights = NULL;
	info->objs = NULL;
}
