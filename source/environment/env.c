/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:02:30 by atorma            #+#    #+#             */
/*   Updated: 2024/07/19 16:37:55 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**env_clone(char **envp)
{
	char	**ret;
	int		i;

	i = 0;
	while (envp && envp[i])
		i++;
	ret = ft_calloc(1, ((i + 1) * sizeof(char *)));
	if (!ret)
		return (NULL);
	i = 0;
	while (envp && envp[i])
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

void	env_sort(char **env)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*tmp;

	i = 0;
	size = args_count(env);
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	env_print(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
}
