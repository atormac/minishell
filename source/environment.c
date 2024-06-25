/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:30:53 by atorma            #+#    #+#             */
/*   Updated: 2024/06/25 14:56:22 by atorma           ###   ########.fr       */
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
		printf("ms->env[%d]: %s\n", i, ms->env[i]);
		i++;
	}
	ms->env[i] = NULL;
	return (1);
}

int	env_var_remove(char **env, char *var)
{
	int		i;
	size_t	var_len;

	if (!env || !var)
		return (1);
	i = 0;
	var_len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_len) == 0)
		{
			env[i] = '\0';
			break;
		}
	}
	return (1);
}
