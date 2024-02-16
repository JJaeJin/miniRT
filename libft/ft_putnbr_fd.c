/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:04:05 by dongyeuk          #+#    #+#             */
/*   Updated: 2023/10/10 16:23:52 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_arr(char *arr, unsigned int n)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	while (i < 10)
		arr[i++] = 0;
	i = 0;
	while (n > 0)
	{
		arr[i++] = n % 10 + '0';
		n = n / 10;
	}
	j = 0;
	while (j < i / 2)
	{
		temp = arr[j];
		arr[j] = arr[i - 1 - j];
		arr[i - 1 - j] = temp;
		j++;
	}
	return (i);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	arr[10];
	int		count;

	if (n < 0)
	{
		write(fd, "-", 1);
		n = ~n + 1;
	}
	else if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	count = set_arr(arr, (unsigned int)n);
	write(fd, arr, count);
}
