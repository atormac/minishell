/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:47:40 by atorma            #+#    #+#             */
/*   Updated: 2024/07/15 19:49:08 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"
#include "../../include/environment.h"

static int	is_numeric(char *s)
{
	if ((*s == '-' || *s == '+') && *(s + 1))
		s++;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int	builtin_exit(t_ms *ms, char **args)
{
	int	code;

	ms->do_exit = 1;
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (args[0] == NULL)
		return (0);
	if (!is_numeric(args[0]))
	{
		error_builtin("exit", args[0], "numeric argument required");
		return (2);
	}
	if (args_count(args) > 1)
	{
		error_print("exit", "too many arguments");
		return (1);
	}
	code = ft_atoi(args[0]);
	return (code);
}
