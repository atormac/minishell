/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:19:33 by atorma            #+#    #+#             */
/*   Updated: 2024/07/15 18:20:31 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"
#include "../../include/environment.h"

static void	export_print(char **env)
{
	size_t	i;
	char	*eq;

	i = 0;
	while (env[i])
	{
		eq = ft_strchr(env[i], '=');
		if (eq)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			write(STDOUT_FILENO, env[i], (eq - env[i]) + 1);
			printf("\"%s\"\n", eq + 1);
		}
		i++;
	}
}

int	builtin_export(t_ms *ms, char **args)
{
	int		i;
	char	*val;

	i = 0;
	if (args[0] == NULL)
	{
		export_print(ms->env);
		return (0);
	}
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
