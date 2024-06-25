/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:30:53 by atorma            #+#    #+#             */
/*   Updated: 2024/06/25 16:32:31 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

//Clones envp to ms->env
int	env_init(t_ms *ms, char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (1);
	while (envp[i])
		i++;
	ms->env = malloc((i + 1) * sizeof(char*));
	if (!ms->env)
		return (0);
	i = 0;
	while (envp[i])
	{
		ms->env[i] = ft_strdup(envp[i]);
		if (!ms->env[i])
		{
			free_array(ms->env);
			return (0);
		}
		i++;
	}
	ms->env[i] = NULL;
	return (1);
}

void	env_print(char **env)
{
	int	i;

	printf("--- env ---\n");
	if (!env)
	{
		printf("env is NULL\n");
		return ;
	}
	i = 0;
	while (env[i])
	{
		printf("env[%d]: %s\n", i, env[i]);
		i++;
	}
}

char	*env_var_get(char **env, char *var)
{
	int		i;
	size_t	var_len;

	if (!env || !var)
		return (NULL);
	i = 0;
	var_len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_len) == 0 && *(env[i] + var_len) == '=')
			return (env[i] + var_len + 1);
		i++;
	}
	return (NULL);
}

void	env_var_remove(char **env, char *var)
{
	size_t	len;
	char	*env_var;

	env_var = env_var_get(env, var);
	if (!env_var)
		return ;
	len = ft_strlen(var);
	*(env_var - len - 1) = '\0';
}
