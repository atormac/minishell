/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:06:02 by atorma            #+#    #+#             */
/*   Updated: 2024/04/18 15:43:24 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	n;
	size_t	src_len;

	n = dstsize;
	src_len = ft_strlen(src);
	while (n > 1 && *src)
	{
		*dst++ = *src++;
		n--;
	}
	if (dstsize != 0)
		*dst = 0;
	return (src_len);
}
