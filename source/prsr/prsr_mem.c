/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsr_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:37:12 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/05 11:38:15 by lopoka           ###   ########.fr       */
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
	return (new_node);
}

void	ft_free_ast(t_ast *ast)
{
	t_ast	*curr;
	t_ast	*tmp;

	if (!ast)
		return ;
	if (ast->left)
		ft_free_ast(ast->left);
	if (ast->right)
		ft_free_ast(ast->right);
	if (ast->str)
		free(ast->str);
	if (ast->io)
	{
		curr = ast->io;
		while (curr)
		{
			tmp = curr;
			free(curr->str);
			curr = curr->io;
			free(tmp);
		}
	}
	free(ast);
}

