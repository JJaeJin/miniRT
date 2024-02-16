/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:33:55 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/01/03 16:51:12 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	flag;
	size_t	count;

	i = 0;
	flag = 1;
	count = 0;
	while (*(s + i) != 0)
	{
		if (*(s + i) == c)
		{
			if (flag == 0)
			{
				count++;
				flag = 1;
			}
		}
		else
			flag = 0;
		i++;
	}
	if (flag == 0)
		count++;
	return (count);
}

static int	malloc_word(char **ans, char *s, char *start_ptr, size_t word_idx)
{
	ans[word_idx] = (char *)ft_calloc(s - start_ptr + 1, 1);
	ft_strlcpy(ans[word_idx], start_ptr, s - start_ptr + 1);
	return (TRUE);
}

static int	split_words(char **ans, char *s, char c, size_t count)
{
	size_t	word_idx;
	char	flag;
	char	*start_ptr;

	flag = 1;
	word_idx = 0;
	while (count > word_idx && *s != 0)
	{
		if (*s == c)
		{
			if (flag == 0)
				if (!malloc_word(ans, s, start_ptr, word_idx++))
					return (--word_idx);
			flag = 1;
		}
		else if (flag == 1)
		{
			start_ptr = s;
			flag = 0;
		}
		s++;
	}
	if (count > word_idx && !malloc_word(ans, s, start_ptr, word_idx++))
		return (--word_idx);
	return (word_idx);
}

char	**ft_split(char const *s, char c)
{
	char	**ans;
	size_t	i;
	size_t	count;
	size_t	result_count;

	count = count_words(s, c);
	ans = (char **)ft_calloc(count + 1, sizeof(char *));
	result_count = split_words(ans, (char *)s, c, count);
	if (result_count != count)
	{
		i = 0;
		while (i < result_count)
			free(ans[i++]);
		free(ans);
		return (FALSE);
	}
	ans[count] = 0;
	return (ans);
}
