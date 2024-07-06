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

void	heredoc_unlink(void)
{
	char	filepath[256];

	heredoc_filepath(0, filepath);
	if (access(filepath, F_OK) == 0)
		unlink(filepath);
}

int	heredoc_fd(void)
{
	int fd;
	char	filepath[256];

	heredoc_filepath(0, filepath);
	fd = open(filepath, O_RDONLY, 0644);
	if (fd == -1)
		error_print(filepath, NULL);
	heredoc_unlink();
	return (fd);
}

int	heredoc_prompt(char *eof)
{
	int		fd;
	char	*line;
	char	filepath[256];

	heredoc_filepath(1, filepath);
	fd = open(filepath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		error_print(filepath, NULL);
		return (0);
	}
	while (1)
	{
		line = readline(">");
		if (!line || ft_strcmp(line, eof) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	return (1);
}
