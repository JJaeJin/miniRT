/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:59:54 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/01/03 16:48:02 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr_s;
	unsigned char	unsigned_c;

	ptr_s = (unsigned char *)s;
	unsigned_c = (unsigned char)c;
	while (n > 0)
	{
		if (*ptr_s == unsigned_c)
			return ((void *)ptr_s);
		ptr_s++;
		n--;
	}
	return (FALSE);
}
