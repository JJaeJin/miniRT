/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:10:04 by dongyeuk          #+#    #+#             */
/*   Updated: 2023/10/10 16:25:07 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr_s;
	char	*ptr_c;
	char	ch_c;

	ch_c = (char)c;
	ptr_c = 0;
	ptr_s = (char *)s;
	while (*ptr_s != '\0')
	{
		if (*ptr_s == ch_c)
			ptr_c = ptr_s;
		ptr_s++;
	}
	if (ch_c == '\0')
		return (ptr_s);
	return (ptr_c);
}
