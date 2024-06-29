/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:30:53 by atorma            #+#    #+#             */
/*   Updated: 2024/06/26 20:36:54 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**env_clone(char **envp)
{
	char	**ret;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	ret = ft_calloc(1, ((i + 1) * sizeof(char*)));
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
	return (ret);
}

void	env_print(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		if (env[i][0] != '\0')
			printf("%s\n", env[i]);
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


void	env_var_unset(char **env, char *var)
{
	size_t	len;
	char	*env_var;

	env_var = env_var_get(env, var);
	if (!env_var)
		return ;
	len = ft_strlen(var);
	*(env_var - len - 1) = '\0';
}

static int	env_var_add(t_ms *ms, char *var_str)
{
	char	**new;
	int		i;

	i = 0;
	while (ms->env && ms->env[i])
		i++;
	new = ft_calloc(1, (i + 2) * sizeof(char*));
	if (!new)
		return (0);
	ft_memcpy(new, ms->env, i * sizeof(char*));
	new[i] = var_str;
	free(ms->env);
	ms->env = new;
	return (1);
}

static int find_ptr_index(char **env, char *var)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = env_var_get(env, var);
	if (ptr)
		ptr = ptr - ft_strlen(var) - 1;
	while (env[i])
	{
		if (ptr && env[i] == ptr)
				return (i);
		else if (!ptr && env[i][0] == '\0')
				return (i);
		i++;
	}
	return (-1);
}

int	env_var_set(t_ms *ms, char *var, char *val)
{
	int		index;
	char	*new;
	size_t	new_len;

	new_len = ft_strlen(var) + ft_strlen(val) + 2;
	new = ft_calloc(1, new_len);
	if (!new)
		return (0);
	ft_strlcat(new, var, new_len);
	ft_strlcat(new, "=", new_len);
	ft_strlcat(new, val, new_len);
	index = find_ptr_index(ms->env, var);
	if (index == -1)
	{
		if (!env_var_add(ms, new))
		{
			free(new);
			return (0);
		}
		return (1);
	}
	free(ms->env[index]);
	ms->env[index] = new;
	return (1);
}
