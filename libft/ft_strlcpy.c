/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:38:09 by dongyeuk          #+#    #+#             */
/*   Updated: 2023/10/17 12:13:55 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;

	count = 0;
	while (src[count] != '\0' && dstsize > 1)
	{
		dst[count] = src[count];
		dstsize--;
		count++;
	}
	dst[count] = '\0';
	return (count);
}
