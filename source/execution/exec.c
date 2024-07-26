/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:31 by atorma            #+#    #+#             */
/*   Updated: 2024/07/26 16:06:58 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"
#include "../../include/signals.h"

char	*path_join(char *path, char *bin);
char	**path_get(char **envp);
char	*path_find_bin(t_ms *ms, char *cmd);
int		redirect(t_ms *ms, t_ast *ast, int cmd_id, int *prev_fd);
int		heredoc_prompt(t_ms *ms, t_ast *ast);
void	std_save(t_ms *ms);
void	std_reset(t_ms *ms);

static int	exec_builtin(t_ms *ms, int id, char **args)
{
	int	ret;

	ret = 0;
	if (id == BUILTIN_ECHO)
		builtin_echo(args);
	else if (id == BUILTIN_PWD)
		printf("%s\n", ms->cwd);
	else if (id == BUILTIN_ENV || id == BUILTIN_EXPORT || id == BUILTIN_UNSET)
		ret = builtin_env(ms, id, args);
	else if (id == BUILTIN_CD)
		ret = builtin_cd(ms, args, args[0]);
	else if (id == BUILTIN_EXIT)
		ret = builtin_exit(ms, args);
	ms->exit_code = ret;
	return (1);
}

static int	exec_bin(t_ms *ms, char **args)
{
	int		ret;
	char	*cmd_path;

	ret = 0;
	cmd_path = path_find_bin(ms, args[0]);
	if (cmd_path)
		ret = execve(cmd_path, args, ms->env);
	free(cmd_path);
	return (ret);
}

static void	exec_fork(t_ms *ms, t_ast *cmd, int cmd_id, int *prev_fd)
{
	int		builtin;

	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		error_print("fork", NULL);
		minishell_close(ms->pipe);
		minishell_close(prev_fd);
		return ;
	}
	if (cmd->pid == 0)
	{
		ms->is_parent = 0;
		set_signals(ms, SIGNALS_DEFAULT);
		builtin = is_builtin(cmd->expd_str[0]);
		if (redirect(ms, cmd, cmd_id, prev_fd))
		{
			if (builtin)
				exec_builtin(ms, builtin, &cmd->expd_str[1]);
			else
				exec_bin(ms, cmd->expd_str);
		}
		minishell_cleanup(ms);
		exit(ms->exit_code);
	}
}

static void	exec_piped(t_ms *ms, t_ast *cmd, int cmd_id)
{
	int		prev_fd[2];

	cmd->pid = -1;
	prev_fd[0] = ms->pipe[0];
	prev_fd[1] = ms->pipe[1];
	if (cmd_id < CMD_LAST)
	{
		if (pipe(ms->pipe) == -1)
		{
			error_print("pipe", NULL);
			minishell_close(prev_fd);
			return ;
		}
	}
	exec_fork(ms, cmd, cmd_id, prev_fd);
	close(ms->pipe[1]);
	ms->pipe[1] = -1;
	if (cmd_id > CMD_FIRST)
		close(prev_fd[0]);
}

void	exec_cmd(t_ms *ms, t_ast *cmd, int cmd_id)
{
	int	builtin;

	if (cmd->expd_str[0] == NULL)
		return ;
	builtin = is_builtin(cmd->expd_str[0]);
	if (builtin && cmd_id == CMD_NOPIPE)
	{
		std_save(ms);
		if (redirect(ms, cmd, cmd_id, NULL))
			exec_builtin(ms, builtin, &cmd->expd_str[1]);
		std_reset(ms);
	}
	else if (cmd_id == CMD_NOPIPE)
		exec_fork(ms, cmd, cmd_id, NULL);
	else
		exec_piped(ms, cmd, cmd_id);
	if (cmd->pid == -1)
		ms->abort = 1;
}
