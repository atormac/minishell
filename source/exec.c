/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:31 by atorma            #+#    #+#             */
/*   Updated: 2024/06/26 20:35:32 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtin.h"

int		redirect(t_ms *ms, t_ast *ast, int cmd_id, int *prev_fd);
int		pid_wait(pid_t pid);

static int	exec_builtin(t_ms *ms, int id, char **args)
{
	if (id == BUILTIN_ECHO)
		builtin_echo(args);
	else if (id == BUILTIN_PWD)
		printf("%s\n", ms->cwd);
	else if (id == BUILTIN_ENV || id == BUILTIN_EXPORT || id == BUILTIN_UNSET)
		builtin_env(ms, id, args);
	else if (id == BUILTIN_CD)
		return builtin_cd(ms, args);
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
	pid_t pid = fork();
	if (pid == 0)
	{
		if (redirect(ms, ast, cmd_id, prev_fd))
			exec_bin(ms, args);
		exit(0);
	}
	return (pid);
}

static pid_t	exec_piped(t_ms *ms, t_ast *ast, int cmd_id, char **args)
{
	pid_t	pid;
	int	prev_fd[2];
	int	pipefd[2];

	prev_fd[0] = ms->pipe_read;
	prev_fd[1] = ms->pipe_write;
	if (cmd_id < CMD_LAST)
	{
		close(prev_fd[1]);
		pipe(pipefd);
		ms->pipe_read = pipefd[0];
		ms->pipe_write = pipefd[1];
	}
	pid = exec_fork(ms, ast, cmd_id, prev_fd, args);
	close(prev_fd[0]);
	return (pid);
}


int	exec_ast(t_ms *ms, t_ast *ast, int cmd_id)
{
	int	ret;
	int	builtin;
	char	**args;
	pid_t	pid;

	ret = 0;
	args = ft_split(ast->str, ' ');
	if (args[0] == NULL)
		return (0);
	builtin = is_builtin(args[0]);
	if (builtin != BUILTIN_NONE)
		ret = exec_builtin(ms, builtin, &args[1]);
	else
	{
		if (cmd_id == CMD_NOPIPE)
			pid = exec_fork(ms, ast, cmd_id, NULL, args);
		else
			pid = exec_piped(ms, ast, cmd_id, args);
		ast->pid = pid;
	}
	free_array(args);
	return (ret);
}
