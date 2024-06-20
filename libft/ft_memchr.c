/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:11:22 by atorma            #+#    #+#             */
/*   Updated: 2024/04/18 17:24:47 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	f;

	str = (unsigned char *)s;
	f = (unsigned char)c;
	while (n > 0)
	{
		if (*str == f)
			return (str);
		str++;
		n--;
	}
	return (NULL);
}
