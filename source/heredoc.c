#include "../include/minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <readline/readline.h>

#define HEREDOC_FILE "/tmp/heredoc_ms"

int	heredoc_fd(void)
{
	int fd;

	fd = open(HEREDOC_FILE, O_RDONLY, 0644);
	if (fd == -1)
		error_print(HEREDOC_FILE, NULL);
	unlink(HEREDOC_FILE);
	return (fd);
}

int	heredoc_prompt(char *eof)
{
	int		fd;
	char	*line;

	fd = open(HEREDOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		error_print(HEREDOC_FILE, NULL);
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
