/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:03:31 by atorma            #+#    #+#             */
/*   Updated: 2024/07/23 16:21:37 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	//static int	c;

	if (count && SIZE_MAX / count < size)
		return (NULL);
	//if (c == 7)
	//	return (NULL);
	p = malloc(count * size);
	//c++;
	if (!p)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}
