#include "../include/minishell.h"

#include <stdio.h>

char	*exec_path_get(t_ms *ms, char *cmd);

int main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	ms.envp = envp;
	if (argc == 2)
	{
		if (is_builtin(argv[1]))
			printf("is_builtin\n");
		char	*cmd_path = exec_path_get(&ms, argv[1]);
		printf("cmd_path: %s\n", cmd_path);
	}
	return (0);
}
