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

int	open_infile(t_ms *ms, t_ast *io, int *to_fd)
{
	int		fd;

	*to_fd = STDIN_FILENO;
	if (io->type == 6)
		return (ms->fd_heredoc);
	fd = open(io->expd_str[0], O_RDONLY, 0644);
	return (fd);
}

int	open_outfile(t_ast *io, int *to_fd)
{
	int		fd;
	int		flags;

	*to_fd = STDOUT_FILENO;
	flags = O_CREAT | O_WRONLY | O_TRUNC;
	if (io->type == 7)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	fd = open(io->expd_str[0], flags, 0644);
	return (fd);
}

static int	redirect_io(t_ms *ms, t_ast *io)
{
	int	fd;
	int	to_fd;

	if (io->type == 6 || io->type == 3)
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
	return (1);
}

int	redirect(t_ms *ms, t_ast *ast, int cmd_id, int *prev_fd)
{
	int	ret;

	if (ast->io && !redirect_io(ms, ast->io))
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

