/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:43:17 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/25 20:08:57 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

size_t	args_count(char **args)
{
	size_t	ret;

	ret = 0;
	if (!args)
		return (ret);
	while (args[ret])
		ret++;
	return (ret);
}

int	is_export_valid(char *str)
{
	if (*str == '\0' || ft_isdigit(*str))
		return (0);
	while (*str && *str != '=')
	{
		if (*str == '_')
		{
			str++;
			continue ;
		}
		if (!ft_isalnum(*str))
			return (0);
		str++;
	}
	return (1);
}

int	pid_wait(t_ast *cmd)
{
	int		status;
	int		sig;

	if (cmd->pid < 0)
		return (-1);
	if (waitpid(cmd->pid, &status, 0) < 0)
		return (-1);
	cmd->pid = -2;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		else if (sig == SIGSEGV)
			ft_putstr_fd("Segmentation fault: 11\n", STDERR_FILENO);
		else if (sig == SIGINT)
			ft_putstr_fd("\n", STDERR_FILENO);
		return (sig + 128);
	}
	return (EXIT_FAILURE);
}

int	event(void)
{
	return (0);
}

ssize_t	line_write(int fd, char *str)
{
	if (str && write(fd, str, ft_strlen(str)) == -1)
		return (0);
	if (write(fd, "\n", 1) == -1)
		return (0);
	return (1);
}
