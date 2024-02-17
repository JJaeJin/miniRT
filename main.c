/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:26:12 by jaejilee          #+#    #+#             */
/*   Updated: 2024/02/17 12:37:37 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mr.h"

int main(int argc, char *argv[])
{
	
	
	if (argc != 2)
	{
		write(2, "Error\nminiRT: wrong argument count\n", 35);
		return (1);
	}
	

	return (0);
}
