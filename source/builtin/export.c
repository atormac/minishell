/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:19:33 by atorma            #+#    #+#             */
/*   Updated: 2024/07/15 19:22:36 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"
#include "../../include/environment.h"

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

static int	is_alnum(char *str)
{
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	export_var(t_ms *ms, char *arg)
{
	char	*val;

	if (ft_isdigit(arg[0]))
		return (1);
	val = ft_strchr(arg, '=');
	if (!val)
	{
		if (!is_alnum(arg))
			return (1);
		return (0);
	}
	*val = '\0';
	if (!is_alnum(arg))
		return (1);
	val++;
	env_var_set(ms, arg, val);
	return (0);
}

void	error_export(char *str);

int	builtin_export(t_ms *ms, char **args)
{
	int	i;

	i = 0;
	if (args[0] == NULL)
		return (export_print(ms->env));
	while (args[i])
	{
		if (export_var(ms, args[i]) == 1)
		{
			error_export(args[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
