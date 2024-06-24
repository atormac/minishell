#include "../include/minishell.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static	int	minishell_init(t_ms *ms, char **argv, char **envp)
{
	ms->envp = envp;
	ms->cwd = malloc(256);

	getcwd(ms->cwd, 256);

	printf("ms->cwd: %s\n", ms->cwd);
	printf("minishell initialized\n");
	(void)argv;
	return (1);
}

static	void	minishell(t_ms *ms)
{
	char	*line;

	(void)ms;
	while (1)
	{
		line = readline("minishell: ");
		if (line == NULL)
			break;
		if (*line)
		{
			add_history(line);
			printf("line: %s\n", line);
		}
		free(line);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	(void)argc;
	if (!minishell_init(&ms, argv, envp))
	{
		ft_putstr_fd("Error initializing minishell\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}

	minishell(&ms);
	return (0);
}
