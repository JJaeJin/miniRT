/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:19:09 by jaejilee          #+#    #+#             */
/*   Updated: 2024/02/20 15:19:01 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "argument.h"

int	is_double(char *s, double *f)
{
	int	i;

	if (ft_isdigit(s[0]) == FALSE)
		return (FALSE);
	i = 0;
	while (ft_isdigit(s[i]) == TRUE)
		i++;
	if (s[i] != '.' && s[i] != 0)
		return (FALSE);
	if (s[i] == '.')
	{
		i++;
		while (ft_isdigit(s[i]) == TRUE)
			i++;
		if (s[i] != 0)
			return (FALSE);
	}
	if (ft_atod(s + i, f) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	is_unsigned_double(char *s, double *f)
{
	int	i;

	if (ft_isdigit(s[0]) == FALSE)
		return (FALSE);
	i = 0;
	while (ft_isdigit(s[i]) == TRUE)
		i++;
	if (s[i] != '.' && s[i] != 0)
		return (FALSE);
	if (s[i] == '.')
	{
		i++;
		while (ft_isdigit(s[i]) == TRUE)
			i++;
		if (s[i] != 0)
			return (FALSE);
	}
	if (ft_atod(s + i, f) == FALSE \
		|| f <= 0)
		return (FALSE);
	return (TRUE);
}
