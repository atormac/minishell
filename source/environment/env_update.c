/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:41:56 by atorma            #+#    #+#             */
/*   Updated: 2024/07/15 19:43:14 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/environment.h"

int	env_update_shlvl(t_ms *ms)
{
	char	*level;
	int		new_lvl;

	level = env_var_get(ms->env, "SHLVL");
	if (!level)
	{
		env_var_set(ms, "SHLVL", "1");
		return (1);
	}
	new_lvl = ft_atoi(level) + 1;
	level = ft_itoa(new_lvl);
	if (!level)
		return (0);
	env_var_set(ms, "SHLVL", level);
	free(level);
	return (1);
}

int	env_set_cwd(t_ms *ms)
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

int	env_update_cwd(t_ms *ms)
{
	char	*dir;
	char	*pwd_exists;

	dir = getcwd(NULL, 0);
	if (!dir)
		return (0);
	pwd_exists = env_var_get(ms->env, "PWD");
	if (!pwd_exists)
	{
		env_var_set(ms, "OLDPWD", "");
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