/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:33:28 by dongyeuk          #+#    #+#             */
/*   Updated: 2023/10/10 16:23:40 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{	
	char	*dst_ch;
	char	*src_ch;

	dst_ch = (char *)dst;
	src_ch = (char *)src;
	if (dst_ch == 0 && src_ch == 0 && n != 0)
		return (dst);
	while (n-- > 0)
		dst_ch[n] = src_ch[n];
	return (dst);
}
