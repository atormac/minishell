/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:19:33 by atorma            #+#    #+#             */
/*   Updated: 2024/07/19 18:26:20 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"
#include "../../include/environment.h"

int		is_export_valid(char *str);
void	error_export(char *str);

static void	print_entry(char *entry)
{
	char	*eq;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	eq = ft_strchr(entry, '=');
	if (eq)
	{
		write(STDOUT_FILENO, entry, (eq - entry) + 1);
		printf("\"%s\"\n", eq + 1);
	}
	else
		printf("%s\n", entry);
}

static int	export_print(char **env)
{
	size_t	i;
	char	**sorted;

	i = 0;
	sorted = env_clone(env);
	if (!sorted)
		return (1);
	env_sort(sorted);
	while (sorted[i])
	{
		if (sorted[i][0] != '\0')
			print_entry(sorted[i]);
		i++;
	}
	free_array(sorted);
	return (0);
}

static void	remove_eq(t_ms *ms, char *arg)
{
	char	*ptr;

	ptr = env_var_get(ms->env, arg);
	if (!ptr)
		return ;
	*(ptr - 1) = '\0';
}

static int	export_var(t_ms *ms, char *arg)
{
	char	*val;

	if (!is_export_valid(arg))
		return (1);
	val = ft_strchr(arg, '=');
	if (!val)
	{
		env_var_set(ms, arg, "");
		remove_eq(ms, arg);
		return (0);
	}
	*val = '\0';
	val++;
	env_var_set(ms, arg, val);
	return (0);
}

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
