/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:49:13 by jaejilee          #+#    #+#             */
/*   Updated: 2024/02/20 11:22:50 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_atoi_expand(const char *nptr, double *ans);
static void		ft_paraset(unsigned long *max_num, int *lim_num, int sign, \
						unsigned long *acc);

double	ft_atod(char *s)
{

}

static double	ft_atoi_expand(const char *nptr, double *ans)
{
	unsigned long	acc;
	unsigned long	max_num;
	int				lim_num;

	while (*nptr == ' ' || (9 <= *nptr && *nptr <= 13))
		nptr++;
	ft_paraset(&max_num, &lim_num, 1, &acc);
	while ('0' <= *nptr && *nptr <= '9')
	{
		acc = acc * 10 + *nptr - '0';
		if (acc > max_num || (acc == (max_num / 10) && *(nptr + 1) > lim_num))
			return (FALSE);
		nptr++;
	}
	*ans = acc;
	return (TRUE);
}

static void	ft_paraset(unsigned long *max_num, int *lim_num, int sign, \
						unsigned long *acc)
{
	int	size;

	*acc = 0;
	size = sizeof(long long) * sizeof(void *);
	*max_num = (sign) * ((unsigned long long)1 << (size - 1)) - (sign > 0);
	*lim_num = (*max_num % 10) + '0';
}
