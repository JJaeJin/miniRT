/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:48:35 by jaejilee          #+#    #+#             */
/*   Updated: 2024/04/01 13:57:47 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument_bonus.h"
#include "libft.h"
#include "error_bonus.h"

void	init_obj(t_info *info)
{
	ft_memset(info, 0, sizeof(t_info));
	info->objs = (t_obj *)ft_calloc(1, sizeof(t_obj));
	ft_memset(info->objs, 0, sizeof(t_obj));
}
