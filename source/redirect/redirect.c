/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:14:21 by atorma            #+#    #+#             */
/*   Updated: 2024/07/24 16:47:51 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <fcntl.h>

static int	open_infile(t_ms *ms, t_ast *io, int *to_fd)
{
	int		fd;

	*to_fd = STDIN_FILENO;
	if (io->type == t_lwrlwr)
	{
		ms->heredoc_done = 1;
		return (ms->fd_heredoc);
	}
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

static int	redirect_io(t_ms *ms, t_ast *io, int *redir_fd)
{
	int	fd;
	int	to_fd;

	if (io->type != t_lwrlwr && (!io->expd_str || !io->expd_str[0]))
	{
		error_print(io->str, "ambiguous redirect");
		return (0);
	}
	if (io->type == t_lwrlwr || io->type == t_lwr)
		fd = open_infile(ms, io, &to_fd);
	else
		fd = open_outfile(io, &to_fd);
	if (fd == -1)
	{
		error_print(io->expd_str[0], NULL);
		return (0);
	}
	if (dup2(fd, to_fd) == -1)
		error_print("dup2", NULL);
	close(fd);
	*redir_fd = to_fd;
	return (1);
}

static int	redirect_io_inout(t_ms *ms, t_ast *ast, int *redir_fd)
{
	t_ast	*io;

	io = ast->io;
	ms->heredoc_done = 0;
	*redir_fd = -1;
	while (io)
	{
		if (ms->heredoc_done && io->type == t_lwrlwr)
		{
			io = io->io;
			continue ;
		}
		if (!redirect_io(ms, io, redir_fd))
		{
			ms->exit_code = 1;
			return (0);
		}
		io = io->io;
	}
	return (1);
}

int	redirect(t_ms *ms, t_ast *ast, int cmd_id, int *prev_fd)
{
	int	ret;
	int	redir_fd;

	if (!redirect_io_inout(ms, ast, &redir_fd))
		return (0);
	if (cmd_id == CMD_NOPIPE)
		return (1);
	ret = 1;
	if (cmd_id > CMD_FIRST && redir_fd != 0 && dup2(prev_fd[0], 0) == -1)
	{
		error_print("dup2", NULL);
		ret = 0;
	}
	if (cmd_id < CMD_LAST && redir_fd != 1 && dup2(ms->pipe[1], 1) == -1)
	{
		error_print("dup2", NULL);
		ret = 0;
	}
	minishell_close(ms->pipe);
	if (cmd_id < CMD_LAST && prev_fd[0] >= 0)
		close(prev_fd[0]);
	return (ret);
}
