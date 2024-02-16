/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:56:16 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/01/03 16:53:07 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t			idx;
	unsigned char	*ptr_s1;
	unsigned char	*ptr_s2;

	idx = 0;
	ptr_s1 = (unsigned char *)s1;
	ptr_s2 = (unsigned char *)s2;
	while ((ptr_s1[idx] != '\0' || ptr_s2[idx] != '\0') && idx < n)
	{
		if (ptr_s1[idx] != ptr_s2[idx])
			return ((size_t)(ptr_s1[idx] - ptr_s2[idx]));
		idx++;
	}
	return (FALSE);
}
