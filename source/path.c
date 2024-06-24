#include "../include/minishell.h"

char	*path_join(char *path, char *bin)
{
	char	*ret;
	size_t	path_len;
	size_t	bin_len;

	path_len = ft_strlen(path);
	bin_len = ft_strlen(bin);
	ret = malloc(path_len + bin_len + 2);
	if (!ret)
		return (NULL);
	if (ft_strchr(bin, '/'))
	{
		ft_strlcpy(ret, bin, bin_len + 1);
		return (ret);
	}
	ft_strlcpy(ret, path, path_len + 1);
	ft_strlcpy(ret + path_len, "/", 2);
	ft_strlcpy(ret + path_len + 1, bin, bin_len + 1);
	return (ret);
}

char	**path_get(char **envp)
{
	int		i;
	char	**arr;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			arr = ft_split(envp[i] + 5, ':');
			return (arr);
		}
		i++;
	}
	return (NULL);
}

char	*path_find_bin(t_ms *ms, char *cmd)
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
