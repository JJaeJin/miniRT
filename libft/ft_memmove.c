/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:10:45 by dongyeuk          #+#    #+#             */
/*   Updated: 2023/10/10 16:23:42 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_ch;
	char	*src_ch;
	size_t	i;

	i = -1;
	dst_ch = (char *)dst;
	src_ch = (char *)src;
	if (len != 0 && dst == 0 && src == 0)
		return (dst);
	if (dst_ch > src_ch)
		while (len-- > 0)
			dst_ch[len] = src_ch[len];
	else
		while (++i < len)
			dst_ch[i] = src_ch[i];
	return (dst);
}
