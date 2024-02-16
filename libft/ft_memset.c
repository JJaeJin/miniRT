/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:16:31 by dongyeuk          #+#    #+#             */
/*   Updated: 2023/10/10 16:23:45 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*trgt_str;
	unsigned char	input_data;

	input_data = (unsigned char)c;
	trgt_str = (unsigned char *)b;
	while (len-- > 0)
		trgt_str[len] = input_data;
	return (b);
}
