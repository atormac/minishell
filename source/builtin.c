/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:23 by atorma            #+#    #+#             */
/*   Updated: 2024/07/05 18:44:40 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtin.h"
#include "../include/environment.h"

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

	if (!args)
	{
		printf("\n");
		return ;
	}
	i = 0;
	newline = 1;
	if (ft_strcmp(args[0], "-n") == 0)
	{
		newline = 0;
		i = 1;
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

int	builtin_cd(t_ms *ms, char **args)
{
	char	*dir;

	if (args_count(args) != 1)
	{
		error_print("cd", "too many arguments");
		return (1);
	}
	dir = args[0];
	if (chdir(dir) == -1)
	{
		error_builtin("cd", dir, NULL);
		return (1);
	}
	if (!update_cwd(ms))
		return (1);
	return (0);
}

static int	builtin_export(t_ms *ms, char *str)
{
	char	*val;

	val = ft_strchr(str, '=');
	if (!val || val == str)
		return (1);
	*val = '\0';
	val++;
	env_var_set(ms, str, val);
	return (0);
}

int	builtin_env(t_ms *ms, int id, char **args)
{
	size_t	arg_cnt;

	arg_cnt = args_count(args);
	if (id == BUILTIN_ENV)
	{
		if (arg_cnt != 0)
			return (2);
		env_print(ms->env);
	}
	else if (id == BUILTIN_EXPORT)
	{
		if (arg_cnt != 1)
			return (2);
		return (builtin_export(ms, args[0]));
	}
	else if (id == BUILTIN_UNSET)
	{
		if (arg_cnt != 1)
			return (2);
		env_var_unset(ms->env, args[0]);
	}
	return (0);
}
