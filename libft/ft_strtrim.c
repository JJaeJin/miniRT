/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 10:19:17 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/01/03 16:41:49 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_needle(char *needles, unsigned char *set)
{
	int	i;

	i = 0;
	while (i < 256)
		needles[i++] = 0;
	i = 0;
	while (*(set + i) != 0)
	{
		needles[*(set + i)] = 1;
		i++;
	}
}

static size_t	get_start_pos(unsigned char *ptr_s1, char *needles)
{
	size_t	j;

	j = 0;
	while (needles[ptr_s1[j]] == 1)
		j++;
	return (j);
}

static size_t	get_end_pos(unsigned char *ptr_s1, char *needles, size_t len)
{
	while (len != 0 && needles[ptr_s1[len - 1]] == 1)
		len--;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	needles[256];
	char	*ans;
	char	*ptr_s1;
	size_t	start_pos;
	size_t	len;

	len = ft_strlen(s1);
	if (len == 0)
		return (ft_calloc(1, 1));
	ptr_s1 = (char *)s1;
	set_needle(needles, (unsigned char *)set);
	start_pos = get_start_pos((unsigned char *)ptr_s1, needles);
	len = get_end_pos((unsigned char *)ptr_s1, needles, len);
	if (start_pos > len)
		return (ft_calloc(1, 1));
	ans = (char *)ft_calloc(len - start_pos + 1, 1);
	ft_strlcpy(ans, ptr_s1 + start_pos, len - start_pos + 1);
	return (ans);
}
