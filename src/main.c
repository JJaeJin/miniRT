/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:26:12 by jaejilee          #+#    #+#             */
/*   Updated: 2024/02/20 13:42:13 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include "libft.h"
#include "error.h"

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
	// 실행부~~
	free_all_info(&info);
	return (SUCCESS);
}
