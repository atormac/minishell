/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:31 by atorma            #+#    #+#             */
/*   Updated: 2024/07/15 19:36:38 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

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

static void	exec_fork(t_ms *ms, t_ast *ast, int cmd_id, int *prev_fd)
{
	int		builtin;

	ast->pid = fork();
	if (ast->pid == -1)
	{
		error_print("fork", NULL);
		close(ms->pipe_read);
		close(ms->pipe_write);
		return ;
	}
	if (ast->pid == 0)
	{
		builtin = is_builtin(ast->expd_str[0]);
		if (redirect(ms, ast, cmd_id, prev_fd))
		{
			if (builtin)
				exec_builtin(ms, builtin, &ast->expd_str[1]);
			else
				exec_bin(ms, ast->expd_str);
		}
		minishell_cleanup(ms);
		exit(ms->exit_code);
	}
}

static void	exec_piped(t_ms *ms, t_ast *ast, int cmd_id)
{
	int		prev_fd[2];
	int		pipefd[2];

	ast->pid = -1;
	prev_fd[0] = ms->pipe_read;
	prev_fd[1] = ms->pipe_write;
	if (cmd_id < CMD_LAST)
	{
		if (pipe(pipefd) == -1)
		{
			error_print("pipe", NULL);
			return ;
		}
		ms->pipe_read = pipefd[0];
		ms->pipe_write = pipefd[1];
	}
	exec_fork(ms, ast, cmd_id, prev_fd);
	close(ms->pipe_write);
	if (cmd_id > CMD_FIRST)
		close(prev_fd[0]);
}

void	exec_cmd(t_ms *ms, t_ast *ast, int cmd_id)
{
	int	builtin;

	if (ast->io && ast->io->type == t_lwrlwr)
	{
		if (!heredoc_prompt(ms, ast->io->expd_str[0]))
			return ;
	}
	builtin = is_builtin(ast->expd_str[0]);
	if (builtin && !ast->io && cmd_id == CMD_NOPIPE)
		exec_builtin(ms, builtin, &ast->expd_str[1]);
	else if (cmd_id == CMD_NOPIPE)
		exec_fork(ms, ast, cmd_id, NULL);
	else
		exec_piped(ms, ast, cmd_id);
	if (ms->fd_heredoc >= 0)
		close(ms->fd_heredoc);
	if (ast->pid == -1)
		ms->cmd_error = 1;
}
