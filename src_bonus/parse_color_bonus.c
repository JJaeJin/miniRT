/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 20:33:10 by jaejilee          #+#    #+#             */
/*   Updated: 2024/04/01 13:57:47 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "argument_bonus.h"

static int	is_num(char *s, int *i, double *vi);
static int	is_comma(char *s, int *i);
static int	is_end(char *s, int i);
static int	is_in_color(double c);

int	is_rgb(char *s, t_color *clr)
{
	int	i;

	i = 0;
	if (is_num(s, &i, &(clr->red)) == FALSE)
		return (FALSE);
	if (is_comma(s, &i) == FALSE)
		return (FALSE);
	if (is_num(s, &i, &(clr->green)) == FALSE)
		return (FALSE);
	if (is_comma(s, &i) == FALSE)
		return (FALSE);
	if (is_num(s, &i, &(clr->blue)) == FALSE)
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
	if (is_in_color(*vi) == FALSE)
		return (FALSE);
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

static int	is_in_color(double c)
{
	if (c >= 0 && c <= 255)
		return (TRUE);
	return (FALSE);
}
