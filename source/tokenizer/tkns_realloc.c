/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkns_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:28:07 by lopoka            #+#    #+#             */
/*   Updated: 2024/06/25 19:55:25 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tokenizer.h"
#include <stdlib.h>
#include <stdio.h>

void	ft_free_tkns(t_tkn_arr *tkns)
{
	int	i;

	i = 0;
	while (i < tkns->i)
		free(tkns->arr[i++].str);
	free(tkns->arr);
}

void	ft_tkns_realloc(t_tkn_arr *tkns)
{
	void	*dst;

	if (tkns->i < tkns->size)
		return ;
	dst = (void *) malloc(tkns->size * sizeof(t_tkn) + tkns->to_add * sizeof(t_tkn));
	if (!dst)
	{
		ft_free_tkns(tkns);
		tkns->err = 1;
		return ;
	}
	ft_memmove(dst, tkns->arr, tkns->size * sizeof(t_tkn));
	ft_free_tkns(tkns);
	tkns->arr = dst;
	tkns->size += tkns->to_add;
}
