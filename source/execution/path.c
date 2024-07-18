/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:18 by atorma            #+#    #+#             */
/*   Updated: 2024/07/15 19:37:35 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/stat.h>

int		check_cmd_initial(t_ms *ms, char *cmd);
int		check_path_cmd(t_ms *ms, char *cmd, char *cmd_path, int err);

char	*path_join(char *path, char *bin, int *err)
{
	char	*ret;
	size_t	path_len;
	size_t	bin_len;

	path_len = ft_strlen(path);
	bin_len = ft_strlen(bin);
	ret = malloc(path_len + bin_len + 2);
	if (!ret)
	{
		*err = 1;
		error_print("malloc", NULL);
		return (NULL);
	}
	ft_strlcpy(ret, path, path_len + 1);
	ft_strlcpy(ret + path_len, "/", 2);
	ft_strlcpy(ret + path_len + 1, bin, bin_len + 1);
	return (ret);
}

char	**path_get(char **envp, int *err)
{
	char	**arr;
	char	*path;

	*err = 0;
	path = env_var_get(envp, "PATH");
	if (!path)
		return (NULL);
	arr = ft_split(path, ':');
	if (!arr)
	{
		*err = 1;
		error_print("malloc", NULL);
	}
	return (arr);
}

static char	*path_search(t_ms *ms, char *cmd, int *err)
{
	char	*cmd_path;
	char	**path;
	size_t	i;

	i = 0;
	cmd_path = NULL;
	path = path_get(ms->env, err);
	while (!*err && path && path[i])
	{
		cmd_path = path_join(path[i], cmd, err);
		if (!cmd_path || access(cmd_path, F_OK) == 0)
			break ;
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	free_array(path);
	return (cmd_path);
}

char	*path_abs_or_relative(t_ms *ms, char *cmd)
{
	ms->exit_code = check_cmd(cmd);
	if (ms->exit_code != 0)
		return (NULL);
	return (ft_strdup(cmd));
}

char	*path_find_bin(t_ms *ms, char *cmd)
{
	char	*cmd_path;
	int		err;

	err = 0;
	if (check_cmd_initial(ms, cmd))
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		cmd_path = path_abs_or_relative(ms, cmd);
		return (cmd_path);
	}
	cmd_path = path_search(ms, cmd, &err);
	if (!check_path_cmd(ms, cmd, cmd_path, err))
	{
		free(cmd_path);
		return (NULL);
	}
	return (cmd_path);
}
