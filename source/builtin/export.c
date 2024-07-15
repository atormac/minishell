/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:19:33 by atorma            #+#    #+#             */
/*   Updated: 2024/07/15 18:52:59 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"
#include "../../include/environment.h"

static void	env_sort(char **env)
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

static int	export_print(char **env)
{
	size_t	i;
	char	*eq;
	char	**sorted;

	i = 0;
	sorted = env_clone(env);
	if (!sorted)
		return (1);
	env_sort(sorted);
	while (sorted[i])
	{
		eq = ft_strchr(sorted[i], '=');
		if (eq)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			write(STDOUT_FILENO, sorted[i], (eq - sorted[i]) + 1);
			printf("\"%s\"\n", eq + 1);
		}
		i++;
	}
	free_array(sorted);
	return (0);
}

int	builtin_export(t_ms *ms, char **args)
{
	int		i;
	char	*val;

	i = 0;
	if (args[0] == NULL)
		return (export_print(ms->env));
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
