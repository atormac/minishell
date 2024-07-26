/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:31:19 by atorma            #+#    #+#             */
/*   Updated: 2024/07/26 16:46:04 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		heredoc_loop(t_ms *ms, t_ast *ast);

void	redirect_heredoc(t_ms *ms, t_ast *ast)
{
	if (!ast || ms->abort || ms->stop_heredoc)
		return ;
	if (ast->type == t_cmnd && ast->io && ast->io->type == t_lwrlwr)
	{
		if (!heredoc_loop(ms, ast))
			return ;
	}
	if (ast->left)
		redirect_heredoc(ms, ast->left);
	if (ast->right)
		redirect_heredoc(ms, ast->right);
}
