/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsr_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:32:37 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/17 20:48:49 by lucas            ###   ########.fr       */
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
		printf("%s | ", ast->expd_str[i]);
		i++;
	}
	printf("\n");
}

void	ft_print_ast(t_ms *ms, t_ast *ast, int expd)
{
	if (!ast)
		return ;
	if (!expd)
		printf("Ast type %d, str %s\n", ast->type, ast->str);
	if (expd && ast->expd_str)
		ft_print_expanded(ast);
	ft_print_ast(ms, ast->io, expd);
	ft_print_ast(ms, ast->left, expd);
	ft_print_ast(ms, ast->right, expd);
}
