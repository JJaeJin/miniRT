/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:19:09 by jaejilee          #+#    #+#             */
/*   Updated: 2024/02/20 11:24:01 by jaejilee         ###   ########.fr       */
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
	if (ft_atod() == FALSE)
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
	if (ft_atod() == FALSE \
		|| f <= 0)
		return (FALSE);
	return (TRUE);
}
