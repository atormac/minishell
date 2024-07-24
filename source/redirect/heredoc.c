/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:30:08 by atorma            #+#    #+#             */
/*   Updated: 2024/07/24 17:24:36 by atorma           ###   ########.fr       */
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
	set_signals(ms, SIGNALS_HEREDOC);
	while (1)
	{
		line = readline(">");
		if (!line || ms->stop_heredoc || ft_strcmp(line, io->str) == 0)
			break ;
		success = heredoc_write(ms, write_fd, line, io->do_hrdc_exp);
		if (!success)
			break ;
		free(line);
		line = NULL;
	}
	set_signals(ms, SIGNALS_PARENT);
	if (!line)
		error_heredoc(io->str);
	free(line);
	if (ms->stop_heredoc)
		return (0);
	return (success);
}

static void	heredoc_prompt_empty(t_ms *ms, char *eof)
{
	char	*line;

	set_signals(ms, SIGNALS_HEREDOC);
	while (1)
	{
		line = readline(">");
		if (!line || ms->stop_heredoc || ft_strcmp(line, eof) == 0)
			break ;
		free(line);
		line = NULL;
	}
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

	ms->abort = 1;
	ms->fd_heredoc = -1;
	if (!heredoc_file(&write_fd, &read_fd))
		return (0);
	success = heredoc_read(ms, io, write_fd);
	close(write_fd);
	if (!success)
		close(read_fd);
	ms->fd_heredoc = read_fd;
	if (success)
		ms->abort = 0;
	return (success);
}

int	heredoc_loop(t_ms *ms, t_ast *cmd)
{
	t_ast	*io;

	io = cmd->io;
	while (io && io->type == t_lwrlwr)
	{
		if (cmd->str && io->io == NULL)
			return (heredoc_prompt(ms, io));
		else
			heredoc_prompt_empty(ms, io->str);
		io = io->io;
	}
	return (1);
}
