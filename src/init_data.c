/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:48:35 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/28 18:50:01 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "libft.h"
#include "error.h"

void	init_obj(t_info *info)
{
	ft_memset(info, 0, sizeof(t_info));
	info->objs = (t_obj *)ft_calloc(1, sizeof(t_obj));
	ft_memset(info->objs, 0, sizeof(t_obj));
}
