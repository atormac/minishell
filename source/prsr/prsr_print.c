/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsr_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:32:37 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/12 16:50:09 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_print_expanded(t_ast *ast)
{
	int	i;

	i = 0;
	printf("Expanded cmnd: ");
	while (ast->expd_str[i])
	{
		printf("%s ", ast->expd_str[i]);
		i++;
	}
	printf("\n");
}

void	ft_print_ast(t_ms *ms, t_ast *ast, int expd)
{
	t_ast	*curr;

	if (!ast)
		return ;
	if (!expd)
	{
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
	}
	if (expd && ast->expd_str)
		ft_print_expanded(ast);
	if (ast->io)
		ft_print_ast(ms, ast->io, expd);
	if (ast->left)
		ft_print_ast(ms, ast->left, expd);
	if (ast->right)
		ft_print_ast(ms, ast->right, expd);
}
