/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 09:56:49 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/01/03 16:31:54 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = (char *)ft_calloc(s1_len + s2_len + 1, 1);
	ft_strlcpy(res, (char *)s1, s1_len + 1);
	ft_strlcpy(res + s1_len, (char *)s2, s2_len + 1);
	return (res);
}
