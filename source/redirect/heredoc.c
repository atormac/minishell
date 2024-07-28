/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:30:08 by atorma            #+#    #+#             */
/*   Updated: 2024/07/26 16:04:47 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
#include "../../include/signals.h"
#include <readline/readline.h>

char	*ft_expd_heredoc(char *s, t_ms *ms);
void	error_heredoc(char *eof);
ssize_t	line_write(int fd, char *str);
int		heredoc_file(int *out_write, int *out_read);

static int	heredoc_write(t_ms *ms, int fd, char *line, int do_expand)
{
	ssize_t	ret;
	char	*str;

	str = line;
	if (do_expand)
	{
		str = ft_expd_heredoc(line, ms);
		if (!str)
			return (0);
	}
	ret = line_write(fd, str);
	if (do_expand)
		free(str);
	return (ret);
}

static int	heredoc_read(t_ms *ms, t_ast *io, int write_fd)
{
	int		success;
	char	*line;

	success = 1;
	ms->exit_code = 0;
	set_signals(ms, SIGNALS_HEREDOC);
	while (1)
	{
		line = readline(">");
		if (!line || ms->exit_code == 130 || ft_strcmp(line, io->str) == 0)
			break ;
		success = heredoc_write(ms, write_fd, line, io->do_hrdc_exp);
		if (!success)
			break ;
		free(line);
		line = NULL;
	}
	if (ms->exit_code == 130)
		ms->stop_heredoc = 1;
	set_signals(ms, SIGNALS_PARENT);
	if (!line)
		error_heredoc(io->str);
	free(line);
	return (success);
}

static void	heredoc_prompt_empty(t_ms *ms, char *eof)
{
	char	*line;

	ms->exit_code = 0;
	set_signals(ms, SIGNALS_HEREDOC);
	while (1)
	{
		line = readline(">");
		if (!line || ms->exit_code == 130 || ft_strcmp(line, eof) == 0)
			break ;
		free(line);
		line = NULL;
	}
	if (ms->exit_code == 130)
		ms->stop_heredoc = 1;
	set_signals(ms, SIGNALS_PARENT);
	if (!line)
		error_heredoc(eof);
	free(line);
}

static int	heredoc_prompt(t_ms *ms, t_ast *io)
{
	int		write_fd;
	int		read_fd;
	int		success;

	if (!heredoc_file(&write_fd, &read_fd))
	{
		ms->abort = 1;
		return (0);
	}
	success = heredoc_read(ms, io, write_fd);
	close(write_fd);
	if (!success || ms->stop_heredoc)
	{
		if (!success)
			ms->abort = 1;
		close(read_fd);
		return (0);
	}
	io->fd_heredoc = read_fd;
	return (success);
}

int	heredoc_loop(t_ms *ms, t_ast *cmd)
{
	t_ast	*io;

	io = cmd->io;
	while (io && io->type == t_lwrlwr)
	{
		io->fd_heredoc = -2;
		if (cmd->str && (io->io == NULL || io->io->type != t_lwrlwr))
			return (heredoc_prompt(ms, io));
		else
			heredoc_prompt_empty(ms, io->str);
		if (ms->stop_heredoc)
			return (0);
		io = io->io;
	}
	return (1);
}
