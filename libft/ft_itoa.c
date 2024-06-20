/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:36:09 by atorma            #+#    #+#             */
/*   Updated: 2024/04/18 15:38:38 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_length(long long num)
{
	int	length;

	length = 1;
	if (num < 0)
	{
		length++;
		num *= -1;
	}
	while (num >= 10)
	{
		num /= 10;
		length++;
	}
	return (length);
}

static void	rev_str(char *s, int n)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	if (n < 0)
		i++;
	j = ft_strlen(s) - 1;
	while (s[i] && i <= j)
	{
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
		i++;
		j--;
	}
}

char	*ft_itoa(int n)
{
	long long	num;
	int			length;
	char		*result;
	int			i;

	num = n;
	i = 0;
	length = ft_get_length(num);
	result = malloc(length + 1);
	if (!result)
		return (NULL);
	if (n < 0)
	{
		result[i++] = '-';
		num *= -1;
	}
	while (i < length)
	{
		result[i] = '0' + (num % 10);
		num /= 10;
		i++;
	}
	result[i] = 0;
	rev_str(result, n);
	return (result);
}
