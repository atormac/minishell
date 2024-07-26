/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:47:40 by atorma            #+#    #+#             */
/*   Updated: 2024/07/26 17:27:48 by lopoka           ###   ########.fr       */
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
	/*int		is_negative;

	is_negative = 0;
	if (*s == '-')
	{
		s++;
		is_negative = 1;
	}
	len = ft_strlen(s);
	if (len > (sizeof("9223372036854775807") - 1))
		return (1);
	if (len == (sizeof("9223372036854775807") - 1))
	{
		if (!is_negative && ft_strcmp(s, "9223372036854775807") > 0)
				return (1);
		if (is_negative && ft_strcmp(s, "9223372036854775808") > 0)
			return (1);
	}
	return (0);*/
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
	code = ft_atoi(args[0]);
	return (code);
}
