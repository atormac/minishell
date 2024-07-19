/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:23 by atorma            #+#    #+#             */
/*   Updated: 2024/07/19 18:15:45 by atorma           ###   ########.fr       */
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
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
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

int	builtin_env(t_ms *ms, int id, char **args)
{
	int		i;

	i = -1;
	if (id == BUILTIN_ENV)
	{
		if (!env_var_get(ms->env, "PATH"))
		{
			error_print("env", "No such file or directory");
			return (127);
		}
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
