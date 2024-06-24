/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:31 by atorma            #+#    #+#             */
/*   Updated: 2024/06/24 16:27:33 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_builtin(t_ms *ms, char	*cmd, char **args)
{
	(void)ms;
	(void)cmd;
	(void)args;
	return (1);
}


int	exec_bin(t_ms *ms, char	*cmd, char **args)
{			
	int		ret;
	char	*cmd_path;

	cmd_path = path_find_bin(ms, cmd);
	if (!cmd_path)
		return (0);
	ret = execve(cmd, args, ms->envp);
	free(cmd_path);
	return (ret);
}

int	exec_cmd(t_ms *ms, char *cmd, char **args)
{
	int	ret;
	int	builtin;

	builtin = is_builtin(cmd);
	if (builtin != BUILTIN_NONE)
		ret = exec_builtin(ms, cmd, args);
	else
		ret = exec_bin(ms, cmd, args);
	return (ret);
}
