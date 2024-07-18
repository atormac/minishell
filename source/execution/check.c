/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:36:35 by atorma            #+#    #+#             */
/*   Updated: 2024/07/15 20:38:32 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/environment.h"
#include <sys/stat.h>

void	error_cmd(char *s);

int	check_cmd_is_dot(char *cmd)
{
	if (cmd[0] == '.' && cmd[1] == '\0')
	{
		error_print(cmd,
			"filename argument required\n.: usage: . filename [arguments]");
		return (1);
	}
	return (0);
}

int	check_cmd(char *cmd)
{
	struct stat	file_stat;

	if (access(cmd, F_OK) != 0)
	{
		error_print(cmd, NULL);
		return (127);
	}
	if (access(cmd, X_OK) != 0)
	{
		error_print(cmd, NULL);
		return (126);
	}
	stat(cmd, &file_stat);
	if (S_ISDIR(file_stat.st_mode))
	{
		error_print(cmd, "Is a directory");
		return (126);
	}
	return (0);
}

int	check_path_cmd(t_ms *ms, char *cmd, char *cmd_path)
{
	if (!cmd_path)
	{
		error_cmd(cmd);
		ms->exit_code = 127;
		return (0);
	}
	ms->exit_code = check_cmd(cmd_path);
	if (ms->exit_code != 0)
		return (0);
	return (1);
}
