/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:10:42 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/20 11:20:12 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_paraset(unsigned long *cutoff, int *cutlim, int sign, \
						unsigned long *acc)
{
	int	size;

	*acc = 0;
	size = sizeof(int) * sizeof(void *);
	*cutoff = (sign) * ((int)1 << (size - 1)) - (sign > 0);
	*cutlim = (*cutoff % 10) + '0';
}

static int	ft_strtoi(const char *nptr, int *ans)
{
	unsigned long	acc;
	unsigned long	cutoff;
	int				cutlim;
	int				sign;

	sign = 1;
	if (*nptr == '-')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	ft_paraset(&cutoff, &cutlim, sign, &acc);
	while ('0' <= *nptr && *nptr <= '9')
	{
		acc = acc * 10 + *nptr - '0';
		if (acc > cutoff || (acc == (cutoff / 10) && *(nptr + 1) > cutlim))
			return (FALSE);
		nptr++;
	}
	*ans = acc * sign;
	return (TRUE);
}

int	ft_atod(const char *nptr, double *ans)
{
	int		int_part;
	int		dec_part;
	double	base;

	if (ft_strtoi(nptr, &int_part) == FALSE)
		return (FALSE);
	if (*nptr == '-')
		nptr++;
	while ('0' <= *nptr && *nptr <= '9')
		nptr++;
	if (*nptr == ',' || *nptr == '\0')
	{
		*ans = int_part;
		return (TRUE);
	}
	else if (*nptr != '.')
		return (FALSE);
	nptr++;
	if (ft_strtoi(nptr, &dec_part) == FALSE)
		return (FALSE);
	base = 1;
	while (dec_part / base >= 1)
		base *= 10;
	*ans = int_part + dec_part / base;
	return (TRUE);
}
