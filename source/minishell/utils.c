#include "../../include/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

size_t args_count(char **args)
{
	size_t  ret;
	ret = 0;
	if (!args)
		return (ret);
	while (args[ret])
		ret++;
	return (ret);
}

int	pid_wait(t_ast *cmd)
{
	int		status;

	if (cmd->pid < 0)
		return (-1);
	if (waitpid(cmd->pid, &status, 0) < 0)
		return (-1);
	cmd->pid = -2;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (EXIT_FAILURE);
}

int	pid_kill(pid_t pid)
{
	return (kill(pid, SIGKILL));
}
