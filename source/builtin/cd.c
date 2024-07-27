/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:41:27 by atorma            #+#    #+#             */
/*   Updated: 2024/07/25 19:41:06 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"
#include "../../include/environment.h"

static void	trim_dir(char *path)
{
	char	*last;

	last = ft_strrchr(path, '/');
	if (!last)
		return ;
	if (last == path)
		*(last + 1) = 0;
	else
		*last = 0;
}

static void	trim_path(char *path, char *new, size_t size)
{
	size_t	count;

	count = 0;
	if (ft_strcmp(path, "..") == 0)
		return (trim_dir(new));
	while (*path && ft_strncmp(path, "../", 3) == 0)
	{
		count++;
		path += 3;
	}
	if (!count)
		return ;
	while (count-- > 0)
		trim_dir(new);
	ft_strlcat(new, "/", size);
	ft_strlcat(new, path, size);
}

static int	change_up(t_ms *ms, char *dir)
{
	char	*new;
	size_t	size;

	size = ft_strlen(ms->cwd) + ft_strlen(dir) + 1;
	new = ft_calloc(1, size);
	if (!new)
		return (1);
	ft_strlcat(new, ms->cwd, size);
	trim_path(dir, new, size);
	if (chdir(new) == -1)
	{
		free(new);
		error_builtin("cd", dir, NULL);
		return (0);
	}
	free(new);
	return (1);
}

static int	change_dir(t_ms *ms, char *dir)
{
	if (ft_strcmp(dir, "..") != 0 && ft_strncmp(dir, "../", 3) != 0)
	{
		if (chdir(dir) == -1)
		{
			error_builtin("cd", dir, NULL);
			return (0);
		}
		return (1);
	}
	return (change_up(ms, dir));
}

int	builtin_cd(t_ms *ms, char **args, char *dir)
{
	if (args_count(args) > 1)
	{
		error_print("cd", "too many arguments");
		return (1);
	}
	if (args_count(args) == 1 && args[0][0] == '\0')
		return (0);
	if (!dir)
	{
		dir = env_var_get(ms->env, "HOME");
		if (!dir)
		{
			error_builtin("cd", "HOME not set", "");
			return (1);
		}
	}
	if (!change_dir(ms, dir))
		return (1);
	if (!env_update_cwd(ms))
		return (1);
	return (0);
}
