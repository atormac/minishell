/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:30:08 by atorma            #+#    #+#             */
/*   Updated: 2024/07/19 14:33:39 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
#include "../../include/signals.h"
#include <readline/readline.h>

char	*ft_expd_heredoc(char *s, t_ms *ms);
void	error_heredoc(char *eof);
int		heredoc_file(int *out_write, int *out_read);

static int	heredoc_write(t_ms *ms, int fd, char *line)
{
	char	*expanded;

	expanded = ft_expd_heredoc(line, ms);
	if (!expanded)
		return (0);
	if (write(fd, expanded, ft_strlen(expanded)) == -1)
	{
		free(expanded);
		return (0);
	}
	free(expanded);
	if (write(fd, "\n", 1) == -1)
		return (0);
	return (1);
}

static int	heredoc_read(t_ms *ms, char *eof, int write_fd)
{
	int		success;
	char	*line;

	success = 1;
	set_signals(ms, SIGNALS_HEREDOC);
	while (1)
	{
		line = readline(">");
		if (!line || ms->stop_heredoc || ft_strcmp(line, eof) == 0)
			break ;
		success = heredoc_write(ms, write_fd, line);
		if (!success)
			break ;
		free(line);
		line = NULL;
	}
	set_signals(ms, SIGNALS_PARENT);
	if (!line)
		error_heredoc(eof);
	free(line);
	if (ms->stop_heredoc)
		return (0);
	return (success);
}

int	heredoc_prompt(t_ms *ms, char *eof)
{
	int		write_fd;
	int		read_fd;
	int		success;

	ms->fd_heredoc = -1;
	if (!heredoc_file(&write_fd, &read_fd))
		return (0);
	success = heredoc_read(ms, eof, write_fd);
	close(write_fd);
	if (!success)
		close(read_fd);
	ms->fd_heredoc = read_fd;
	return (success);
}
