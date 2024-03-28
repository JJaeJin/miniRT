/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:48:35 by jaejilee          #+#    #+#             */
/*   Updated: 2024/03/26 15:34:16 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "libft.h"
#include "error.h"

void	init_obj(t_info *info)
{
	ft_memset(info, 0, sizeof(t_info));
	info->objs = (t_obj *)ft_calloc(1, sizeof(t_obj));
}
