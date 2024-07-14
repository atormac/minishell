/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:00:38 by atorma            #+#    #+#             */
/*   Updated: 2024/07/14 18:33:00 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		exec_cmd(t_ms *ms, t_ast *ast, int cmd_id);
int		pid_wait(t_ast *cmd);

static int	command_id(t_ast *cmd, t_ast *prev, t_ast *last_cmd)
{
	static int	entry;

	if (prev->type != t_pipe)
		return (CMD_NOPIPE);
	if (!entry || !last_cmd)
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

void	commands_wait(t_ms *ms, t_ast *ast)
{
	int	tmp;

	if (ast->type == t_cmnd)
	{
		tmp = pid_wait(ast);
		if (tmp >= 0)
			ms->exit_code = tmp;
	}
	if (ast->left)
		commands_wait(ms, ast->left);
	if (ast->right)
		commands_wait(ms, ast->right);
}

static int	commands_can_continue(t_ms *ms, t_ast *last_cmd, int last_type)
{
	int	code;

	if (!last_cmd)
		return (1);
	if (last_type != t_and && last_type != t_or)
		return (1);
	code = pid_wait(last_cmd);
	if (code >= 0)
		ms->exit_code = code;
	if (last_type == t_and && ms->exit_code != 0)
		return (0);
	else if (last_type == t_or && ms->exit_code == 0)
		return (0);
	return (1);
}

void	commands_exec(t_ms *ms, t_ast *ast, t_ast *prev)
{
	static t_ast	*last_cmd;
	static int		last_type;
	int				id;

	if (ast == prev)
		last_cmd = NULL;
	if (ast->type == t_cmnd && ast->expd_str)
	{
		id = command_id(ast, prev, last_cmd);
		exec_cmd(ms, ast, id);
		last_cmd = ast;
		last_type = prev->type;
	}
	if (ast->left)
		commands_exec(ms, ast->left, ast);
	if (ast->right && commands_can_continue(ms, last_cmd, last_type))
		commands_exec(ms, ast->right, ast);
}
