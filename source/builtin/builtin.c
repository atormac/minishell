/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:23 by atorma            #+#    #+#             */
/*   Updated: 2024/07/15 19:47:57 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"
#include "../../include/environment.h"

int	is_builtin(char	*cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (BUILTIN_ECHO);
	if (ft_strcmp(cmd, "cd") == 0)
		return (BUILTIN_CD);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (BUILTIN_PWD);
	if (ft_strcmp(cmd, "export") == 0)
		return (BUILTIN_EXPORT);
	if (ft_strcmp(cmd, "unset") == 0)
		return (BUILTIN_UNSET);
	if (ft_strcmp(cmd, "env") == 0)
		return (BUILTIN_ENV);
	if (ft_strcmp(cmd, "exit") == 0)
		return (BUILTIN_EXIT);
	return (BUILTIN_NONE);
}

void	builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 0;
	newline = 1;
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

int	builtin_cd(t_ms *ms, char **args, char *dir)
{
	if (args_count(args) > 1)
	{
		error_print("cd", "too many arguments");
		return (1);
	}
	if (!dir)
	{
		dir = env_var_get(ms->env, "HOME");
		if (!dir)
		{
			error_builtin("cd", "HOME not set", "");
			return (1);
		}
	}
	if (chdir(dir) == -1)
	{
		error_builtin("cd", dir, NULL);
		return (1);
	}
	if (!env_update_cwd(ms))
		return (1);
	return (0);
}

int	builtin_env(t_ms *ms, int id, char **args)
{
	int		i;

	i = -1;
	if (id == BUILTIN_ENV)
	{
		env_print(ms->env);
		return (0);
	}
	if (id == BUILTIN_EXPORT)
		return (builtin_export(ms, args));
	else if (id == BUILTIN_UNSET)
	{
		while (args[++i])
			env_var_unset(ms->env, args[i]);
	}
	return (0);
}
