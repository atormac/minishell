/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:36:35 by atorma            #+#    #+#             */
/*   Updated: 2024/07/25 18:56:23 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/environment.h"
#include <sys/stat.h>

void	error_cmd(int print_ms, char *s);

int	check_empty(char *cmd)
{
	while (*cmd && *cmd == ' ')
		cmd++;
	if (cmd[0] == '\0')
		return (1);
	return (0);
}

int	check_exists(char *filepath)
{
	struct stat	file_stat;

	if (stat(filepath, &file_stat) == -1)
		return (0);
	if (S_ISREG(file_stat.st_mode))
		return (1);
	return (0);
}

int	check_cmd_initial(t_ms *ms, char *cmd)
{
	if (cmd[0] == '.' && cmd[1] == '\0')
	{
		error_print(cmd,
			"filename argument required\n.: usage: . filename [arguments]");
		ms->exit_code = 2;
		return (1);
	}
	if (check_empty(cmd))
	{
		error_cmd(0, cmd);
		ms->exit_code = 127;
		return (1);
	}
	return (0);
}

int	check_cmd(char *cmd)
{
	struct stat	file_stat;

	if (stat(cmd, &file_stat) == -1)
	{
		error_print(cmd, NULL);
		return (127);
	}
	if (S_ISDIR(file_stat.st_mode))
	{
		error_print(cmd, "Is a directory");
		return (126);
	}
	if (access(cmd, X_OK) != 0)
	{
		error_print(cmd, NULL);
		return (126);
	}
	return (0);
}

int	check_path_cmd(t_ms *ms, char *cmd, char *cmd_path, int err)
{
	if (err)
	{
		ms->exit_code = 1;
		return (0);
	}
	if (!cmd_path)
	{
		error_cmd(0, cmd);
		ms->exit_code = 127;
		return (0);
	}
	ms->exit_code = check_cmd(cmd_path);
	if (ms->exit_code != 0)
		return (0);
	return (1);
}
