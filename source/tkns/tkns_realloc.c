/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkns_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:28:07 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/07 13:54:08 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_free_tkns(t_ms *ms)
{
	size_t	i;

	if (!ms->tkns)
		return ;
	i = 0;
	while (i < ms->tkns->i && ms->tkns->arr)
		free(ms->tkns->arr[i++].str);
	free(ms->tkns->arr);
	free(ms->tkns);
	ms->tkns = 0;
}

void	ft_tkns_realloc(t_ms *ms)
{
	void	*dst;

	if (!ms->tkns || ms->tkns->i < ms->tkns->size)
		return ;
	dst = (t_tkn *) malloc(ms->tkns->size * sizeof(t_tkn)
			+ ms->tkns->to_add * sizeof(t_tkn));
	if (!dst)
		return (ft_free_tkns(ms));
	ft_memmove(dst, ms->tkns->arr, ms->tkns->size * sizeof(t_tkn));
	free(ms->tkns->arr);
	ms->tkns->arr = dst;
	ms->tkns->size += ms->tkns->to_add;
}
