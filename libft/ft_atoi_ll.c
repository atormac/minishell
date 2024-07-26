/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:14:00 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/26 17:16:39 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

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
		res = res * 10 + *str - 48;
		if (res < 0 && sign == 1)
			return (-1);
		if (res < 0 && sign == -1)
			return (0);
		str++;
	}
	return (res * sign);
}
