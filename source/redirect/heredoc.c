/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:30:08 by atorma            #+#    #+#             */
/*   Updated: 2024/07/15 20:31:44 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <readline/readline.h>

char	*ft_expd_heredoc(char *s, t_ms *ms);
void	error_heredoc(char *eof);

static void	heredoc_gen_path(char *out)
{
	static int	counter;
	char		*tmp;

	ft_strlcpy(out, "/tmp/heredoc_ms_", 256);
	counter++;
	tmp = ft_itoa(counter);
	if (tmp)
		ft_strlcat(out, tmp, 256);
	free(tmp);
}

static int	heredoc_file(int *out_write, int *out_read)
{
	int		fd_write;
	int		fd_read;
	char	filepath[256];

	heredoc_gen_path(filepath);
	fd_write = open(filepath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	fd_read = open(filepath, O_RDONLY, 0644);
	if (fd_write == -1 || fd_read == -1)
	{
		error_print("Error creating heredoc tmp file!\n", NULL);
		close(fd_write);
		close(fd_read);
		return (0);
	}
	*out_write = fd_write;
	*out_read = fd_read;
	unlink(filepath);
	return (1);
}

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
	while (1)
	{
		line = readline(">");
		if (!line || ft_strcmp(line, eof) == 0)
			break ;
		success = heredoc_write(ms, write_fd, line);
		if (!success)
			break ;
		free(line);
		line = NULL;
	}
	if (!line)
		error_heredoc(eof);
	free(line);
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
