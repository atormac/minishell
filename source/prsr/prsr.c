/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:04:51 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/05 13:29:32 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_set_prsr_err(t_ms *ms, int type)
{
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
		if (!ast)
			return (ft_set_prsr_err(ms, e_mem), NULL);
	}
	return (ast);
}

t_ast	*ft_prsr(t_tkns *tkns, t_ms *ms)
{
	t_ast	*ast;

	if (!tkns || !ms)
		return (NULL);
	ast = ft_get_ast(tkns, 1, ms);
	if (ft_is_tkn(tkns))
		return (ft_free_ast(ast), ft_set_prsr_err(ms, e_sntx), NULL);
	return (ast);
}
