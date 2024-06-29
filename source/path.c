/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:18 by atorma            #+#    #+#             */
/*   Updated: 2024/06/25 14:49:32 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	*path_search(char **path, char *cmd)
{
	int		i;
	char	*cmd_path;

	i = 0;
	if (ft_strchr(cmd, '/'))
		return (NULL);
	while (path && path[i])
	{
		cmd_path = path_join(path[i], cmd);
		if (!cmd_path)
			break;
		if (is_executable(cmd_path))
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	*path_abs_or_relative(char *cmd)
{
	if (ft_strchr(cmd, '/') == NULL)
		return (NULL);
	if (is_executable(cmd))
		return ft_strdup(cmd);
	return (NULL);
}

char	*path_find_bin(t_ms *ms, char *cmd)
{
	char	**path;
	char	*cmd_path;

	cmd_path = NULL;
	if (cmd[0] == '\0')
		return (NULL);
	path = path_get(ms->env);
	cmd_path = path_search(path, cmd);
	if (!cmd_path)
		cmd_path = path_abs_or_relative(cmd);
	free_array(path);
	return (cmd_path);
}
