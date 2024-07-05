/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsr_branch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:52:44 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/05 13:27:04 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

t_ast	*ft_merge_branch(t_ast *ast, int op, t_ast *new_branch, t_ms *ms)
{
	t_ast	*new_ast;

	if (ms->prsr_err)
		return (ft_free_ast(ast), ft_free_ast(new_branch), NULL);
	if (!new_branch)
		return (ast);
	new_ast = ft_get_ast_node(op);
	if (!new_ast)
		return (ft_free_ast(ast), ft_free_ast(new_branch), NULL);
	new_ast->left = ast;
	new_ast->right = new_branch;
	return (new_ast);
}

t_ast	*ft_get_branch(t_tkns *tkns, t_ms *ms)
{
	t_ast	*branch;

	if (ms->prsr_err)
		return (NULL);
	if (ft_is_tkn_bop(tkns) || tkns->arr[tkns->curr_tkn].type == t_prnths_cls)
		return (ft_set_prsr_err(ms, e_sntx), NULL);
	else if (tkns->arr[tkns->curr_tkn].type == t_prnths_opn)
	{
		tkns->curr_tkn++;
		branch = ft_get_ast(tkns, 1, ms);
		if (!branch)
			return (ft_set_prsr_err(ms, e_mem), NULL);
		if (!ft_is_tkn(tkns) || tkns->arr[tkns->curr_tkn].type != t_prnths_cls)
			return (ft_set_prsr_err(ms, e_sntx), ft_free_ast(branch), NULL);
		tkns->curr_tkn++;
		return (branch);
	}
	else
		return (ft_get_cmnd(tkns, ms));
}
