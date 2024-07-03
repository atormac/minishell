
#include "../include/minishell.h"

void error_print(char *s)
{
	char	buffer[1024];

	ft_strlcpy(buffer, "minishell: ", sizeof(buffer) - 1);
	ft_strlcat(buffer, s, sizeof(buffer) - 1);
	ft_strlcat(buffer, ": ", sizeof(buffer) - 1);
	ft_strlcat(buffer, strerror(errno), sizeof(buffer) - 1);
	ft_strlcat(buffer, "\n", sizeof(buffer));
	ft_putstr_fd(buffer, STDERR_FILENO);
}

void	error_cmd(char *s)
{
	char	buffer[1024];

	ft_strlcpy(buffer, s, sizeof(buffer) - 1);
	ft_strlcat(buffer, ": ", sizeof(buffer) - 1);
	ft_strlcat(buffer, "command not found", sizeof(buffer) - 1);
	ft_strlcat(buffer, "\n", sizeof(buffer));
	ft_putstr_fd(buffer, STDERR_FILENO);
}
