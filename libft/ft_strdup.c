/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 08:54:14 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/01/03 16:26:53 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr_str;
	size_t	ptr_size;

	ptr_size = ft_strlen(s1) + 1;
	ptr_str = (char *)ft_calloc(ptr_size, 1);
	ft_strlcpy(ptr_str, s1, ptr_size);
	return (ptr_str);
}
