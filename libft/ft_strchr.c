/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:10:04 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/01/03 16:52:44 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr_s;
	char	ch_c;

	ptr_s = (char *)s;
	ch_c = (char)c;
	while (*ptr_s != '\0')
	{
		if (*ptr_s == ch_c)
			return (ptr_s);
		ptr_s++;
	}
	if (ch_c == '\0')
		return (ptr_s);
	return (FALSE);
}
