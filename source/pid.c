/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:21:15 by atorma            #+#    #+#             */
/*   Updated: 2024/07/14 18:15:15 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

int	pid_wait(t_ast *cmd)
{
	int		status;

	if (cmd->pid < 0)
		return (-1);
	if (waitpid(cmd->pid, &status, 0) < 0)
		return (-1);
	cmd->pid = -2;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (EXIT_FAILURE);
}

int	pid_kill(pid_t pid)
{
	return (kill(pid, SIGKILL));
}
