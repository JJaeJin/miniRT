/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:19:09 by jaejilee          #+#    #+#             */
/*   Updated: 2024/04/01 13:57:47 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "argument_bonus.h"

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
		if (ft_isdigit(s[i]) == FALSE)
			return (FALSE);
		while (ft_isdigit(s[i]) == TRUE)
			i++;
		if (s[i] != 0)
			return (FALSE);
	}
	if (ft_atod(s, f) == FALSE \
		|| f <= 0)
		return (FALSE);
	return (TRUE);
}
