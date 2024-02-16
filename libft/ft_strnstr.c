/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:24:46 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/01/03 16:53:25 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	idx1;
	size_t	idx2;

	idx1 = 0;
	if (haystack == 0 && len == 0)
		return (FALSE);
	if (*needle == '\0')
		return ((char *)haystack);
	while (*(haystack + idx1) != '\0' && idx1 < len)
	{
		idx2 = 0;
		while (*(haystack + idx1 + idx2) == *(needle + idx2))
		{
			if (*(needle + idx2 + 1) == '\0')
			{
				return ((char *)haystack + idx1);
			}
			if (idx1 + idx2 == len - 1)
				return (FALSE);
			idx2++;
		}
		idx1++;
	}
	return (FALSE);
}
