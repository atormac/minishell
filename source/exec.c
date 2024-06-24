#include "../include/minishell.h"


int	exec_builtin(t_ms *ms, char	*cmd, char **args)
{
	(void)ms;
	(void)cmd;
	(void)args;
	return (1);
}

char	*exec_path_get(t_ms *ms, char *cmd)
{
	int		i;
	char	**path;
	char	*cmd_path;

	i = 0;
	path = path_get(ms->envp);
	if (!path)
		return (NULL);
	while (path[i])
	{
		cmd_path = path_join(path[i], cmd);
		if (!cmd_path)
			break;
		if (access(cmd_path, F_OK) == 0)
		{
			free_array(path);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_array(path);
	return (NULL);
}

int	exec_bin(t_ms *ms, char	*cmd, char **args)
{			
	int		ret;
	char	*cmd_path;

	cmd_path = exec_path_get(ms, cmd);
	if (!cmd_path)
		return (0);
	ret = execve(cmd, args, ms->envp);
	free(cmd_path);
	return (ret);
}

int	exec_cmd(t_ms *ms, char *cmd, char **args)
{
	int	ret;

	if (is_builtin(cmd))
		ret = exec_builtin(ms, cmd, args);
	else
		ret = exec_bin(ms, cmd, args);
	return (ret);
}
