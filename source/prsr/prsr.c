/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:04:51 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/23 17:58:01 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_set_prsr_err(t_ms *ms, int type)
{
	if (!ms->prsr_err)
		ms->prsr_err = type;
}

t_ast	*ft_get_ast(t_tkns *tkns, int tree_top, t_ms *ms)
{
	t_ast	*ast;
	int		op;

	if (!ft_is_tkn(tkns) || ms->prsr_err)
		return (NULL);
	ast = ft_get_branch(tkns, ms);
	if (!ast)
		return (NULL);
	while ((tree_top && ft_is_tkn_bop(tkns))
		|| (!tree_top && ft_is_tkn_bop(tkns) == t_pipe))
	{
		op = tkns->arr[tkns->curr_tkn].type;
		tkns->curr_tkn++;
		if (!ft_is_tkn(tkns))
			return (ft_set_prsr_err(ms, e_sntx), ft_free_ast(ast), NULL);
		ast = ft_merge_branch(ast, op, ft_get_ast(tkns, 0, ms), ms);
		if (ms->prsr_err || !ast)
			return (ft_set_prsr_err(ms, e_mem), NULL);
	}
	return (ast);
}

void	ft_prsr(t_ms *ms)
{
	if (!ms || !ms->tkns || ms->prsr_err)
	{
		ms->ast = NULL;
		return ;
	}
	ms->ast = ft_get_ast(ms->tkns, 1, ms);
	if (ft_is_tkn(ms->tkns))
	{
		ft_free_ast(ms->ast);
		ms->ast = NULL;
		ft_set_prsr_err(ms, e_sntx);
	}
}
