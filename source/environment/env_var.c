/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:21:06 by atorma            #+#    #+#             */
/*   Updated: 2024/07/19 16:44:10 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/environment.h"

static int	find_ptr_index(char **env, char *var)
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
	int		i;
	size_t	var_len;

	if (!env || !var || var[0] == '\0')
		return ;
	i = 0;
	var_len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_len) == 0)
		{
			if (*(env[i] + var_len) == '=' || *(env[i] + var_len) == '\0')
			{
				env[i][0] = '\0';
				return ;
			}
		}
		i++;
	}
}

static int	env_var_add(t_ms *ms, char *var_str)
{
	char	**new;
	int		i;

	i = 0;
	while (ms->env && ms->env[i])
		i++;
	new = ft_calloc(1, (i + 2) * sizeof(char *));
	if (!new)
		return (0);
	ft_memcpy(new, ms->env, i * sizeof(char *));
	new[i] = var_str;
	free(ms->env);
	ms->env = new;
	return (1);
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
