/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsr_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:37:12 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/14 17:09:39 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

t_ast	*ft_get_ast_node(int type)
{
	t_ast	*new_node;

	new_node = (t_ast *) ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	new_node->pid = -2;
	return (new_node);
}

void	ft_free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->str)
		free(ast->str);
	if (ast->expd_str)
		ft_free_split_null(ast->expd_str);
	ft_free_ast(ast->io);
	ft_free_ast(ast->left);
	ft_free_ast(ast->right);
	free(ast);
}
