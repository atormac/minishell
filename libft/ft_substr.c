/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:36:08 by atorma            #+#    #+#             */
/*   Updated: 2024/04/18 16:57:04 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	sub_len;

	if (!s)
		return (NULL);
	sub_len = 0;
	str = NULL;
	if (ft_strlen(s) >= start)
	{
		sub_len = ft_strlen(s + start);
		if (sub_len > len)
			sub_len = len;
	}
	str = malloc(sub_len + 1);
	if (!str)
		return (NULL);
	if (sub_len > 0)
		ft_strlcpy(str, s + start, sub_len + 1);
	else
		str[sub_len] = 0;
	return (str);
}
