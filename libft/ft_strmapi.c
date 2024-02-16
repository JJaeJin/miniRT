/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:11:18 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/01/03 16:31:29 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ans;
	unsigned int	idx;

	idx = 0;
	ans = (char *)ft_calloc(1, ft_strlen(s) + 1);
	while (*(s + idx) != 0)
	{
		*(ans + idx) = f(idx, *(s + idx));
		idx++;
	}
	ans[idx] = 0;
	return (ans);
}
