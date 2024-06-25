/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_tkn_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:28:07 by lopoka            #+#    #+#             */
/*   Updated: 2024/06/25 17:51:58 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tokenizer.h"
#include <stdlib.h>
#include <stdio.h>


void	*ft_realloc(void *src, size_t old_s, size_t add_s)
{
	size_t	i;
	void	*dst;
	char	*c_dst;
	char	*c_src;

	dst = (void *) malloc(old_s + add_s);
	if (!dst)
	{
		free (src);
		return (0);
	}
	c_dst = (char *) dst;
	c_src = (char *) src;
	i = 0;
	while (i < old_s)
	{
		c_dst[i] = c_src[i];
		i++;
	}
	free(src);
	return (dst);
}
/*
int main(void)
{
	t_tkn *arr;
	
	arr = malloc(5 * sizeof(t_tkn));

	arr[2].type = 13;
	
	arr = ft_realloc(arr, 5 * sizeof(t_tkn), 5 * sizeof(t_tkn));

	printf("Type %d\n", arr[2].type);

	free(arr);
	return 0;
}*/
