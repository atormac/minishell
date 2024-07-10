/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:00:38 by atorma            #+#    #+#             */
/*   Updated: 2024/07/10 19:22:33 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		exec_cmd(t_ms *ms, t_ast *ast, int cmd_id);
int		pid_wait(pid_t pid);

static int	command_id(t_ast *ast, t_ast *prev)
{
	static int	entry;

	if (prev->type != t_pipe)
		return (CMD_NOPIPE);
	if (!entry)
	{
		entry = 1;
		return (CMD_FIRST);
	}
	if (prev->right == ast && !ast->left && !ast->right)
	{
		entry = 0;
		return (CMD_LAST);
	}
	return (CMD_MIDDLE);
}

void	commands_wait(t_ms *ms, t_ast *ast)
{
	int	tmp;

	if (ast->type == 0 && ast->pid > 0)
	{
		tmp = pid_wait(ast->pid);
		if (tmp >= 0)
			ms->exit_code = tmp;
	}
	if (ast->left)
		commands_wait(ms, ast->left);
	if (ast->right)
		commands_wait(ms, ast->right);
}

void	commands_exec(t_ms *ms, t_ast *ast, t_ast *prev)
{
	int	id;

	if (ast->type == t_cmnd && ast->expd_str)
	{
		id = command_id(ast, prev);
		exec_cmd(ms, ast, id);
	}
	if (ast->left)
		commands_exec(ms, ast->left, ast);
	if (ast->right)
	{
		if (prev->type == t_and)
		{
			if (prev->left->pid < 0 && ms->exit_code != 0) 
				return ;
			if (prev->left->pid >= 0 && pid_wait(prev->left->pid) != 0)
				return ;
		}
		else if (prev->type == t_or)
		{
			if (prev->left->pid < 0 && ms->exit_code == 0)
				return ;
			if (prev->left->pid >= 0 && pid_wait(prev->left->pid) == 0)
				return ;
		}
		commands_exec(ms, ast->right, ast);
	}
}
