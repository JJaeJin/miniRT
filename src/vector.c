/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejilee <jaejilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:51:51 by jaejilee          #+#    #+#             */
/*   Updated: 2024/02/20 11:25:17 by jaejilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "argument.h"

static int	is_num(char *s, int *i, int *vi);
static int	is_comma(char *s, int *i);
static int	is_end(char *s, int i);

int	is_vector(char *s, t_vector *v)
{
	int	i;

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

static int	is_num(char *s, int *i, int *vi)
{
	if (s[*i] != '-' && ft_isdigit(s[*i]) == FALSE)
		return (FALSE);
	if (ft_atod() == FALSE)
		return (FALSE);
	if (s[*i] == '-')
		(*i)++;
	while (ft_isdigit(s[*i]) == FALSE)
		i++;
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
