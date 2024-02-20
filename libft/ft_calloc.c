/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 08:15:22 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/20 13:33:09 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr_mal_add;

	if (size == 0 || count == 0)
	{
		ptr_mal_add = malloc(0);
		if (ptr_mal_add == 0)
			exit(1);
		return (ptr_mal_add);
	}
	if (size > SIZE_MAX / count)
		exit(1);
	ptr_mal_add = malloc(count * size);
	if (ptr_mal_add == 0)
		exit(return_error("malloc fail"));
	ft_bzero(ptr_mal_add, count * size);
	return (ptr_mal_add);
}
