/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:30:53 by atorma            #+#    #+#             */
/*   Updated: 2024/06/25 17:43:02 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

//Clones envp to ms->env

char	**env_clone(char **envp, int expand_size)
{
	char	**ret;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	ret = malloc((i + 1 + expand_size) * sizeof(char*));
	if (!ret)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		ret[i] = ft_strdup(envp[i]);
		if (!ret[i])
		{
			free_array(ret);
			return (0);
		}
		i++;
	}
	ret[i] = NULL;
	return (ret);
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

int	env_var_set(t_ms *ms, char *var, char *val)
{
	char	**new;
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(var) + ft_strlen(val) + 2;
	while (ms->env[i])
		i++;
	new = ft_calloc(1, (i + 2) * sizeof(char*));
	if (!new)
		return (0);
	ft_memcpy(new, ms->env, i * sizeof(char*));
	new[i] = ft_calloc(1, len);
	if (!new[i])
	{
		free(new);
		return (0);
	}
	ft_strlcat(new[i], var, len);
	ft_strlcat(new[i], "=", len);
	ft_strlcat(new[i], val, len);
	free(ms->env);
	ms->env = new;
	return (1);
}
