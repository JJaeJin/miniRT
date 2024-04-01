/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:51:51 by jaejilee          #+#    #+#             */
/*   Updated: 2024/04/01 13:57:47 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "argument_bonus.h"
#include <math.h>

static int	is_num(char *s, int *i, double *vi);
static int	is_comma(char *s, int *i);
static int	is_end(char *s, int i);

int	is_vector(char *s, t_vector *v)
{
	int		i;

	i = 0;
	if (is_num(s, &i, &(v->x)) == FALSE)
		return (FALSE);
	if (is_comma(s, &i) == FALSE)
		return (FALSE);
	if (is_num(s, &i, &(v->y)) == FALSE)
		return (FALSE);
	if (is_comma(s, &i) == FALSE)
		return (FALSE);
	if (is_num(s, &i, &(v->z)) == FALSE)
		return (FALSE);
	if (is_end(s, i) == FALSE)
		return (FALSE);
	return (TRUE);
}

static int	is_num(char *s, int *i, double *vi)
{
	if (s[*i] != '-' && ft_isdigit(s[*i]) == FALSE)
		return (FALSE);
	if (ft_atod(s + *i, vi) == FALSE)
		return (FALSE);
	if (s[*i] == '-')
	{
		(*i)++;
		if (ft_isdigit(s[*i]) == FALSE)
			return (FALSE);
	}
	while (ft_isdigit(s[*i]) == TRUE)
		(*i)++;
	if (s[*i] == '.')
	{
		(*i)++;
		if (ft_isdigit(s[*i]) == FALSE)
			return (FALSE);
	}
	while (ft_isdigit(s[*i]) == TRUE)
		(*i)++;
	return (TRUE);
}

static int	is_comma(char *s, int *i)
{
	if (s[*i] != ',')
		return (FALSE);
	(*i)++;
	return (TRUE);
}

static int	is_end(char *s, int i)
{
	if (s[i] == 0)
		return (TRUE);
	return (FALSE);
}
