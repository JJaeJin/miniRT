/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:49:35 by dongyeuk          #+#    #+#             */
/*   Updated: 2023/10/10 16:24:23 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	idx1;
	size_t	idx2;
	size_t	init_dst_len;

	if (dst == 0 && dstsize == 0)
		return (ft_strlen(src) + dstsize);
	init_dst_len = ft_strlen(dst);
	idx1 = 0;
	if (init_dst_len >= dstsize)
		return (ft_strlen(src) + dstsize);
	while (*(dst + idx1) != '\0')
	{
		dstsize--;
		idx1++;
	}
	idx2 = 0;
	while (*(src + idx2) != '\0' && dstsize > 1)
	{
		dst[idx1 + idx2] = src[idx2];
		idx2++;
		dstsize--;
	}
	dst[idx1 + idx2] = '\0';
	return (init_dst_len + ft_strlen(src));
}
