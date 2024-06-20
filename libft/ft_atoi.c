/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:34:18 by atorma            #+#    #+#             */
/*   Updated: 2024/06/11 18:56:34 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_whitespace(char c)
{
	if (c == '\t' || c == ' ' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

static int	overflow_ret(const char *str)
{
	if (*str == '-')
		return (0);
	return (-1);
}

static int	is_overflow(const char *str, long res)
{
	long	int_min;

	int_min = 2147483648;
	if (*str == '-')
	{
		if (res > (int_min))
			return (1);
	}
	else
	{
		if (res > INT_MAX)
			return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	long		res;
	const char	*s;

	res = 0;
	s = str;
	while (is_whitespace(*s))
		s++;
	str = s;
	if (*s == '-' || *s == '+')
		s++;
	while (*s && *s >= '0' && *s <= '9')
	{
		res = res * 10 + (*s - '0');
		if (is_overflow(str, res))
			return (overflow_ret(str));
		s++;
	}
	if (res != 0 && *str == '-')
		res *= -1;
	return ((int)(res));
}
