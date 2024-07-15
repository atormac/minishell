/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:23 by atorma            #+#    #+#             */
/*   Updated: 2024/07/15 16:48:55 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtin.h"
#include "../include/environment.h"

int		is_numeric(char *s);

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

int		builtin_exit(t_ms *ms, char **args)
{
	int	code;

	ms->do_exit = 1;
	if (args[0] == NULL)
		return (0);
	if (!is_numeric(args[0]))
	{
		error_builtin("exit", args[0], "numeric argument required");
		return (2);
	}
	code = ft_atoi(args[0]);
	return (code);
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
	if (!update_cwd(ms))
		return (1);
	return (0);
}

static int	builtin_export(t_ms *ms, char **args)
{
	int		i;
	char	*val;

	i = 0;
	while (args[i])
	{
		val = ft_strchr(args[i], '=');
		if (!val || val == args[i])
			return (1);
		*val = '\0';
		val++;
		env_var_set(ms, args[i], val);
		i++;
	}
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
	if (args_count(args) == 0)
		return (2);
	if (id == BUILTIN_EXPORT)
		return (builtin_export(ms, args));
	else if (id == BUILTIN_UNSET)
	{
		while (args[++i])
			env_var_unset(ms->env, args[i]);
	}
	return (0);
}
