#include "../include/minishell.h"

#include <stdio.h>

char	*exec_path_get(t_ms *ms, char *cmd);

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

int main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	if (!minishell_init(&ms, argv, envp))
	{
		ft_putstr_fd("Error initializing minishell\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}

	if (argc == 2)
	{
		if (is_builtin(argv[1]))
			printf("is_builtin\n");
		char	*cmd_path = exec_path_get(&ms, argv[1]);
		printf("cmd_path: %s\n", cmd_path);
	}
	return (0);
}
