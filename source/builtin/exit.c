/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:47:40 by atorma            #+#    #+#             */
/*   Updated: 2024/07/25 19:36:06 by atorma           ###   ########.fr       */
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

static int	is_overflow(char *s)
{
	size_t	len;
	int		res;

	if (*s == '-')
		s++;
	len = ft_strlen(s);
	if (len >= (sizeof("9223372036854775807") - 1))
	{
		if (ft_strcmp(s, "9223372036854775807") > 0)
		{
			res = ft_atoi(s);
			if (res == -1 || res == 0)
				return (1);
		}
	}
	return (0);
}

int	builtin_exit(t_ms *ms, char **args)
{
	int	code;

	ms->do_exit = 1;
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (args[0] == NULL)
		return (ms->exit_code);
	if (!is_numeric(args[0]) || is_overflow(args[0]))
	{
		error_builtin("exit", args[0], "numeric argument required");
		return (2);
	}
	if (args_count(args) > 1)
	{
		ms->do_exit = 0;
		error_print("exit", "too many arguments");
		return (1);
	}
	code = ft_atoi(args[0]);
	return (code);
}
