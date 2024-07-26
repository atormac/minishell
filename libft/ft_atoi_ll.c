/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:14:00 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/26 18:32:22 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <limits.h>

long long	ft_atoi_ll(const char *str)
{
	long long	res;
	long long	sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		if (sign == 1 && ((LLONG_MAX - (*str - 48)) < (res * 10)))
			return (-1);
		if (sign == -1 && ((LLONG_MAX - (*str - 48)) < (res * 10 - 1)))
			return (0);
		res = res * 10 + (*str - 48);
		str++;
	}
	return (res * sign);
}
