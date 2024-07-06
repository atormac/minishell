/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:14:21 by atorma            #+#    #+#             */
/*   Updated: 2024/07/05 19:48:14 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <fcntl.h>

int	open_infile(char *file, int is_heredoc)
{
	int		fd;

	if (is_heredoc)
		file = "heredoc";
	if (access(file, F_OK) == 0 && access(file, R_OK) == -1)
		return (-1);
	fd = open(file, O_RDONLY, 0644);
	return (fd);
}

int	open_outfile(char *file, int is_heredoc)
{
	int		fd;
	int		flags;

	flags = O_CREAT | O_WRONLY | O_TRUNC;
	if (is_heredoc)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
		return (-1);
	fd = open(file, flags, 0644);
	return (fd);
}

static int	redirect_io(t_ast *ast)
{
	int	file_fd;
	int	to_fd;

	to_fd = STDIN_FILENO;
	if (ast->io->type == 4)
	{
		to_fd = STDOUT_FILENO;
		file_fd = open_outfile(ast->io->str, 0);
	}
	else
		file_fd = open_infile(ast->io->str, 0);
	if (file_fd == -1)
	{
		error_print(ast->io->str, NULL);
		return (0);
	}
	if (dup2(file_fd, to_fd) == -1)
		error_print("dup2", NULL);
	close(file_fd);
	return (1);
}

int	redirect(t_ms *ms, t_ast *ast, int cmd_id, int *prev_fd)
{
	int	ret;

	if (ast->io && !redirect_io(ast))
		return (0);
	if (cmd_id == CMD_NOPIPE)
		return (1);
	ret = 1;
	if (cmd_id > CMD_FIRST && dup2(prev_fd[0], STDIN_FILENO) == -1)
	{
			error_print("dup2", NULL);
			ret = 0;
	}
	if (cmd_id < CMD_LAST && dup2(ms->pipe_write, STDOUT_FILENO) == -1)
	{
			error_print("dup2", NULL);
			ret = 0;
	}
	close(ms->pipe_read);
	close(ms->pipe_write);
	if (cmd_id < CMD_LAST)
		close(prev_fd[0]);
	return (ret);
}

