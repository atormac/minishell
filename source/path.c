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

static char	*path_search(t_ms *ms, char *cmd)
{
	int		i;
	char	*cmd_path;
	char	**path;

	i = 0;
	cmd_path = NULL;
	path = path_get(ms->env);
	while (path && path[i])
	{
		cmd_path = path_join(path[i], cmd);
		if (!cmd_path)
			break;
		if (is_executable(cmd_path))
			break;
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	free_array(path);
	return (cmd_path);
}

char	*path_abs_or_relative(char *cmd)
{
	if (is_executable(cmd))
		return ft_strdup(cmd);
	return (NULL);
}

char	*path_find_bin(t_ms *ms, char *cmd)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
		cmd_path = path_abs_or_relative(cmd);
	else
		cmd_path = path_search(ms, cmd);
	return (cmd_path);
}
