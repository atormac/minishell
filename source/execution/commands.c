/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:00:38 by atorma            #+#    #+#             */
/*   Updated: 2024/07/26 16:08:56 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

int		exec_cmd(t_ms *ms, t_ast *cmd, int cmd_id);
int		heredoc_loop(t_ms *ms, t_ast *ast);
int		pid_wait(t_ast *cmd, int *exit_type);

static int	command_id(t_ast *cmd, t_ast *prev, int reset)
{
	static int	entry;

	if (reset)
	{
		entry = 0;
		return (-1);
	}
	if (prev->type != t_pipe)
		return (CMD_NOPIPE);
	if (!entry)
	{
		entry = 1;
		return (CMD_FIRST);
	}
	if (prev->right == cmd && !cmd->left && !cmd->right)
	{
		entry = 0;
		return (CMD_LAST);
	}
	return (CMD_MIDDLE);
}

void	commands_wait(t_ms *ms, t_ast *ast, t_ast *limit)
{
	int	tmp;
	int	exit_type;

	if (ast == limit)
		return ;
	if (ast->type == t_cmnd)
	{
		tmp = pid_wait(ast, &exit_type);
		if (tmp >= 0)
		{
			ms->exit_code = tmp;
			ms->exit_type = exit_type;
		}
	}
	if (ast->left)
		commands_wait(ms, ast->left, limit);
	if (ast->right)
		commands_wait(ms, ast->right, limit);
}

static int	commands_can_continue(t_ms *ms, t_ast *root, t_ast *limit, int op)
{
	if (op != t_and && op != t_or)
		return (1);
	commands_wait(ms, root, limit);
	if (op == t_and && ms->exit_code != 0)
		return (0);
	else if (op == t_or && ms->exit_code == 0)
		return (0);
	return (1);
}

void	commands_exec(t_ms *ms, t_ast *ast, t_ast *prev)
{
	static t_ast	*root;
	int				id;

	if (!ast || ms->abort || ms->stop_heredoc || ms->do_exit)
		return ;
	if (ast == prev)
	{
		root = ast;
		command_id(ast, prev, 1);
	}
	if (ast->type == t_cmnd && ast->expd_str)
	{
		id = command_id(ast, prev, 0);
		if (id == CMD_LAST)
			command_id(ast, prev, 1);
		exec_cmd(ms, ast, id);
	}
	if (ast->left)
		commands_exec(ms, ast->left, ast);
	if (ast->right && commands_can_continue(ms, root, ast->right, ast->type))
		commands_exec(ms, ast->right, ast);
}

void	heredoc_exec(t_ms *ms, t_ast *ast)
{

	if (!ast || ms->abort || ms->stop_heredoc)
		return ;
	if (ast->type == t_cmnd && ast->io && ast->io->type == t_lwrlwr)
	{
		if (!heredoc_loop(ms, ast))
			return ;
	}
	if (ast->left)
		heredoc_exec(ms, ast->left);
	if (ast->right)
		heredoc_exec(ms, ast->right);
}
