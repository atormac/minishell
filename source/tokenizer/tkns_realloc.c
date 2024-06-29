/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkns_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:28:07 by lopoka            #+#    #+#             */
/*   Updated: 2024/06/29 09:17:49 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tokenizer.h"

void	ft_free_tkns(t_tkns **tkns)
{
	int		i;

	if (!*tkns)
		return ;
	i = 0;
	while (i < (*tkns)->i && (*tkns)->arr)
		free((*tkns)->arr[i++].str);
	free((*tkns)->arr);
	free(*tkns);
	*tkns = 0;
}

void	ft_tkns_realloc(t_tkns **tkns)
{
	void	*dst;

	if (!*tkns || (*tkns)->i < (*tkns)->size)
		return ;
	dst = (t_tkn *) malloc((*tkns)->size * sizeof(t_tkn)
			+ (*tkns)->to_add * sizeof(t_tkn));
	if (!dst)
		return (ft_free_tkns(tkns));
	ft_memmove(dst, (*tkns)->arr, (*tkns)->size * sizeof(t_tkn));
	free((*tkns)->arr);
	(*tkns)->arr = dst;
	(*tkns)->size += (*tkns)->to_add;
}
