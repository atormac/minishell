/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:31 by atorma            #+#    #+#             */
/*   Updated: 2024/06/26 20:35:32 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtin.h"

static int	exec_builtin(t_ms *ms, int id, char **args)
{
	if (id == BUILTIN_ECHO)
		builtin_echo(args);
	else if (id == BUILTIN_PWD)
		printf("%s\n", ms->cwd);
	else if (id == BUILTIN_ENV || id == BUILTIN_EXPORT || id == BUILTIN_UNSET)
		builtin_env(ms, id, args);
	else if (id == BUILTIN_CD)
		return builtin_cd(ms, args);
	return (1);
}

static int	exec_bin(t_ms *ms, char	*cmd, char **args)
{			
	int		ret;
	char	*cmd_path;

	ret = 0;
	cmd_path = path_find_bin(ms, cmd);
	if (!cmd_path)
	{
		printf("%s: command not found\n", cmd);
		return (0);
	}
	//ret = execve(cmd, args, ms->env);
	printf("cmd_path %s\n", cmd_path);
	free(cmd_path);
	(void)args;
	return (ret);
}

int	exec_cmd(t_ms *ms, char *cmd, char **args)
{
	int	ret;
	int	builtin;

	args = get_args(&cmd);
	builtin = is_builtin(cmd);
	if (builtin != BUILTIN_NONE)
		ret = exec_builtin(ms, builtin, args);
	else
		ret = exec_bin(ms, cmd, args);
	free_array(args);
	return (ret);
}
