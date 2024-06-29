/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:57:24 by atorma            #+#    #+#             */
/*   Updated: 2024/06/26 20:36:40 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/environment.h"

int	is_executable(char *path)
{
	if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
		return (1);
	return (0);
}

int	set_cwd(t_ms *ms)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
		return (0);
	if (!env_var_set(ms, "PWD", dir))
	{
		free(dir);
		return (0);
	}
	ms->cwd = dir;
	return (1);
}

int	update_cwd(t_ms *ms)
{
	char	*dir;
	char	*pwd_exists;

	dir = getcwd(NULL, 0);
	if (!dir)
		return (0);
	pwd_exists = env_var_get(ms->env, "PWD");
	if (!pwd_exists)
	{
		env_var_unset(ms->env, "OLDPWD");
		free(ms->cwd);
		ms->cwd = dir;
		return (1);
	}
	env_var_set(ms, "PWD", dir);
	env_var_set(ms, "OLDPWD", ms->cwd);
	free(ms->cwd);
	ms->cwd = dir;
	return (1);
}
