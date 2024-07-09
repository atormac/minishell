#include "../include/minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <readline/readline.h>

static void	heredoc_filepath(int new, char *out)
{
	static char	old[256];
	static int	counter;
	char		*tmp;

	if (new)
	{
		ft_strlcpy(old, "/tmp/heredoc_ms_", 256);
		counter++;
		tmp = ft_itoa(counter);
		if (tmp)
			ft_strlcat(old, tmp, 256);
		free(tmp);
	}
	ft_strlcpy(out, old, 256);
}

int heredoc_file(int *out_write, int *out_read)
{
	int		fd_write;
	int		fd_read;
	char	filepath[256];

	heredoc_filepath(1, filepath);
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

int	heredoc_prompt(t_ms *ms, char *eof)
{
	int		write_fd;
	int		read_fd;
	char	*line;

	ms->fd_heredoc = -1;
	if (!heredoc_file(&write_fd, &read_fd))
		return (0);
	while (1)
	{
		line = readline(">");
		if (!line || ft_strcmp(line, eof) == 0)
			break ;
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	free(line);
	close(write_fd);
	ms->fd_heredoc = read_fd;
	return (1);
}
