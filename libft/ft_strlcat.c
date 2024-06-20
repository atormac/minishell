/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:14:24 by atorma            #+#    #+#             */
/*   Updated: 2024/04/18 16:20:29 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	if (dstsize < dst_len)
		return (src_len + dstsize);
	dst += dst_len;
	if (dstsize > 0)
	{
		while ((dst_len + i) < (dstsize - 1) && *src)
		{
			*dst++ = *src++;
			i++;
		}
		if (dst_len <= dstsize)
			*dst = 0;
	}
	return (dst_len + src_len);
}
