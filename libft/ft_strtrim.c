/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:50:40 by atorma            #+#    #+#             */
/*   Updated: 2024/04/18 16:41:15 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		s1_len;
	size_t		alloc_size;
	char		*substr;
	const char	*start;
	const char	*end;

	s1_len = ft_strlen(s1);
	start = s1;
	end = s1 + s1_len - 1;
	while (*start && ft_strchr(set, *start))
		start++;
	while (s1_len > 0 && ft_strchr(set, *end))
	{
		end--;
		s1_len--;
	}
	end++;
	alloc_size = end - start;
	if (end - start < 0)
		alloc_size = 0;
	substr = malloc(alloc_size + 1);
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, start, alloc_size + 1);
	return (substr);
}
