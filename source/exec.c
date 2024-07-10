/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:31 by atorma            #+#    #+#             */
/*   Updated: 2024/07/10 15:12:42 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtin.h"

char	*path_join(char *path, char *bin);
char	**path_get(char **envp);
char	*path_find_bin(t_ms *ms, char *cmd);
int		redirect(t_ms *ms, t_ast *ast, int cmd_id, int *prev_fd);
int		heredoc_prompt(t_ms *ms, char *eof);

static int	exec_builtin(t_ms *ms, int id, char **args)
{
	int	ret;

	ret = 0;
	if (id == BUILTIN_ECHO)
		builtin_echo(args);
	else if (id == BUILTIN_PWD)
		ret = printf("%s\n", ms->cwd);
	else if (id == BUILTIN_ENV || id == BUILTIN_EXPORT || id == BUILTIN_UNSET)
		ret = builtin_env(ms, id, args);
	else if (id == BUILTIN_CD)
		ret = builtin_cd(ms, args);
	ms->exit_code = ret;
	return (1);
}

static int	exec_bin(t_ms *ms, char **args)
{			
	int		ret;
	char	*cmd_path;

	ret = 0;
	cmd_path = path_find_bin(ms, args[0]);
	if (!cmd_path)
		return (0);
	ret = execve(cmd_path, args, ms->env);
	free(cmd_path);
	return (ret);
}

static pid_t exec_fork(t_ms *ms, t_ast *ast, int cmd_id, int *prev_fd, char **args)
{
	pid_t	pid;
	int		builtin;

	pid = fork();
	if (pid == -1)
	{
		error_print("fork", NULL);
		close(ms->pipe_read);
		close(ms->pipe_write);
		return (-1);
	}
	if (pid == 0)
	{
		builtin = is_builtin(args[0]);
		redirect(ms, ast, cmd_id, prev_fd);
		if (builtin)
			exec_builtin(ms, builtin, &args[1]);
		else
			exec_bin(ms, args);
		exit(ms->exit_code);
	}
	return (pid);
}

static pid_t	exec_piped(t_ms *ms, t_ast *ast, int cmd_id, char **args)
{
	int		prev_fd[2];
	int		pipefd[2];
	pid_t	pid;

	prev_fd[0] = ms->pipe_read;
	prev_fd[1] = ms->pipe_write;
	if (cmd_id < CMD_LAST)
	{
		if (pipe(pipefd) == -1)
		{
			error_print("pipe", NULL);
			return (-1);
		}
		ms->pipe_read = pipefd[0];
		ms->pipe_write = pipefd[1];
	}
	pid = exec_fork(ms, ast, cmd_id, prev_fd, args);
	close(ms->pipe_write);
	if (cmd_id > CMD_FIRST)
		close(prev_fd[0]);
	return (pid);
}


void	exec_cmd(t_ms *ms, t_ast *ast, int cmd_id)
{
	int	builtin;
	char	**args;

	ast->pid = -2;
	if (ms->cmd_error)
		return ;
	if (ast->io && ast->io->type == 6)
	{
		if (!heredoc_prompt(ms, ast->io->expd_str[0]))
			return ;
	}
	args = ast->expd_str;
	builtin = is_builtin(args[0]);
	if (builtin && !ast->io && cmd_id == CMD_NOPIPE)
		exec_builtin(ms, builtin, &args[1]);
	else if (cmd_id == CMD_NOPIPE)
		ast->pid = exec_fork(ms, ast, cmd_id, NULL, args);
	else
		ast->pid = exec_piped(ms, ast, cmd_id, args);
	if (ms->fd_heredoc >= 0)
		close(ms->fd_heredoc);
	if (ast->pid == -1)
		ms->cmd_error = 1;
}
