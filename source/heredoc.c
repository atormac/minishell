#include "../include/minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <readline/readline.h>

int	heredoc_fd(void)
{
	int fd;

	fd = open("heredoc", O_RDONLY, 0644);
	unlink("heredoc");
	return (fd);
}

int	heredoc_prompt(char *eof)
{
	int		fd;
	char	*line;

	fd = open("heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		error_print("heredoc", NULL);
		return (0);
	}
	while (1)
	{
		line = readline(">");
		if (line == NULL)
			break;
		if (ft_strncmp(line, eof, ft_strlen(eof)) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	return (1);
}
