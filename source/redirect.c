/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:14:21 by atorma            #+#    #+#             */
/*   Updated: 2024/07/14 16:17:59 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <fcntl.h>

static int	open_infile(t_ms *ms, t_ast *io, int *to_fd)
{
	int		fd;

	*to_fd = STDIN_FILENO;
	if (io->type == t_lwrlwr)
		return (ms->fd_heredoc);
	fd = open(io->expd_str[0], O_RDONLY, 0644);
	return (fd);
}

static int	open_outfile(t_ast *io, int *to_fd)
{
	int		fd;
	int		flags;

	*to_fd = STDOUT_FILENO;
	flags = O_CREAT | O_WRONLY | O_TRUNC;
	if (io->type == t_bgrbgr)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	fd = open(io->expd_str[0], flags, 0644);
	return (fd);
}

static int	redirect_io(t_ms *ms, t_ast *io)
{
	int	fd;
	int	to_fd;

	if (io->type == t_lwrlwr || io->type == t_lwr)
		fd = open_infile(ms, io, &to_fd);
	else
		fd = open_outfile(io, &to_fd);
	if (fd == -1)
	{
		error_print(io->expd_str[0], NULL);
		ms->exit_code = 1;
		return (0);
	}
	if (dup2(fd, to_fd) == -1)
		error_print("dup2", NULL);
	close(fd);
	return (1);
}

static int redirect_io_inout(t_ms *ms, t_ast *ast)
{
	t_ast *io;

	io = ast->io;
	if (!io)
		return (1);
	if (!redirect_io(ms, io))
		return (0);
	io = io->io;
	if (!io)
		return (1);
	if (!redirect_io(ms, io))
		return (0);
	return (1);
}

int	redirect(t_ms *ms, t_ast *ast, int cmd_id, int *prev_fd)
{
	int	ret;

	if (!redirect_io_inout(ms, ast))
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

