/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkns_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:28:07 by lopoka            #+#    #+#             */
/*   Updated: 2024/06/26 11:37:26 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tokenizer.h"
#include <stdlib.h>
#include <stdio.h>

void	ft_free_tkns(t_tkns *tkns)
{
	int	i;

	i = 0;
	while (i < tkns->i)
		free(tkns->arr[i++].str);
	free(tkns->arr);
}

void	ft_tkns_realloc(t_tkns *tkns)
{
	void	*dst;

	if (tkns->i < tkns->size)
		return ;
	dst = (t_tkn *) malloc(tkns->size * sizeof(t_tkn) + tkns->to_add * sizeof(t_tkn));
	if (!dst)
	{
		ft_free_tkns(tkns);
		tkns->err = 1;
		return ;
	}
	ft_memmove(dst, tkns->arr, tkns->size * sizeof(t_tkn));
	free(tkns->arr);
	tkns->arr = dst;
	tkns->size += tkns->to_add;
}
