/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:14:03 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/01/03 16:15:18 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_len(long long n);

char	*ft_itoa(int n)
{
	size_t		len;
	size_t		sign;
	char		*res;
	long long	ln;

	sign = 0;
	ln = (long long)n;
	len = get_len(ln);
	res = (char *)ft_calloc(len + 1, 1);
	res[len] = 0;
	if (ln < 0)
	{
		ln *= -1;
		res[0] = '-';
		sign = 1;
	}
	while (len > sign)
	{
		res[--len] = ln % 10 + '0';
		ln /= 10;
	}
	return (res);
}

static size_t	get_len(long long n)
{
	size_t	res;

	if (n == 0)
		return (1);
	res = 0;
	if (n < 0)
	{
		n *= -1;
		res++;
	}
	while (n > 0)
	{
		res++;
		n /= 10;
	}
	return (res);
}
