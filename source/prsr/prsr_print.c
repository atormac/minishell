/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsr_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:32:37 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/05 13:09:00 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_print_ast(t_ms *ms, t_ast *ast)
{
	t_ast	*curr;

	if (!ast)
		return ;
	printf("Ast type %d, str %s", ast->type, ast->str);
	if (!ast->io)
		printf("\n");
	else
	{
		curr = ast->io;
		while (curr)
		{
			printf(", IO type: %d, s: %s", curr->type, curr->str);
			curr = curr->io;
		}
		printf("\n");
	}
	if (ast->left)
		ft_print_ast(ms, ast->left);
	if (ast->right)
		ft_print_ast(ms, ast->right);
}