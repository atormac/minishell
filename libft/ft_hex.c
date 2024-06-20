/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:16:20 by atorma            #+#    #+#             */
/*   Updated: 2024/04/30 16:16:29 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_hex(struct t_write_state *ws, unsigned int n, int is_lower)
{
	int		i;
	char	tmp;
	char	result[32];

	i = 0;
	while (n != 0)
	{
		tmp = n % 16;
		if ((n % 16) < 10)
			tmp += 48;
		else
			tmp += 55;
		result[i++] = tmp;
		n /= 16;
	}
	while (i-- > 0)
	{
		if (is_lower)
			result[i] = ft_tolower(result[i]);
		print_char(ws, result[i]);
	}
}

void	hex_uint(struct t_write_state *ws, unsigned int n, int is_lower)
{
	if (n == 0)
	{
		print_char(ws, '0');
		return ;
	}
	print_hex(ws, n, is_lower);
}

void	print_hex_ptr(struct t_write_state *ws, unsigned long long n)
{
	int		i;
	char	tmp;
	char	result[32];

	i = 0;
	while (n != 0)
	{
		tmp = n % 16;
		if ((n % 16) < 10)
			tmp += 48;
		else
			tmp += 55;
		result[i++] = tmp;
		n /= 16;
	}
	while (i-- > 0)
	{
		result[i] = ft_tolower(result[i]);
		print_char(ws, result[i]);
	}
}
