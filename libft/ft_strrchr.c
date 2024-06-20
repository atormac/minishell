/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:50:29 by atorma            #+#    #+#             */
/*   Updated: 2024/04/18 15:26:27 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	size;
	char	ch;

	ch = c;
	size = ft_strlen(s);
	while (size > 0 && s[size] != ch)
		size--;
	if (s[size] == ch)
		return ((char *)(s + size));
	return (NULL);
}
