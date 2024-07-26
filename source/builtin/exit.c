/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:47:40 by atorma            #+#    #+#             */
/*   Updated: 2024/07/26 18:31:52 by atorma           ###   ########.fr       */
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
	size_t		len;
	long long	n;

	if (ft_strcmp(s, "-9223372036854775808") == 0)
		return (0);
	len = ft_strlen(s);
	n = ft_atoi_ll(s);
	if ((n == 0 && len != 1) || (n == -1 && len != 2))
		return (1);
	return (0);
}

int	builtin_exit(t_ms *ms, char **args)
{
	int	code;

	ms->do_exit = 1;
	if (isatty(STDIN_FILENO) && ms->is_parent)
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
	if (ft_strcmp(args[0], "-9223372036854775808") == 0)
		code = 0;
	else
		code = ft_atoi(args[0]);
	return (code);
}
