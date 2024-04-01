/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:26:12 by jaejilee          #+#    #+#             */
/*   Updated: 2024/04/01 13:57:47 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument_bonus.h"
#include "libft.h"
#include "error_bonus.h"
#include "draw_bonus.h"

int	main(int argc, char *argv[])
{
	t_info	info;

	if (argc != 2)
		return (return_error("wrong argument count"));
	init_obj(&info);
	if (parse_all(&info, argv[1]) == FAILURE)
	{
		free_all_info(&info);
		return (return_error("wrong file"));
	}
	convert_system(&info);
	draw_all(info);
	free_all_info(&info);
	return (SUCCESS);
}
