/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:23 by atorma            #+#    #+#             */
/*   Updated: 2024/06/26 18:10:18 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

int	is_builtin(char	*cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (BUILTIN_ECHO);
	if (ft_strcmp(cmd, "cd") == 0)
		return (BUILTIN_CD);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (BUILTIN_PWD);
	if (ft_strcmp(cmd, "export") == 0)
		return (BUILTIN_EXPORT);
	if (ft_strcmp(cmd, "unset") == 0)
		return (BUILTIN_UNSET);
	if (ft_strcmp(cmd, "env") == 0)
		return (BUILTIN_ENV);
	if (ft_strcmp(cmd, "exit") == 0)
		return (BUILTIN_EXIT);
	return (BUILTIN_NONE);
}

void	builtin_echo(char **args)
{
	if (!args || !args[0])
		return ;
	if (ft_strcmp(args[0], "-n") == 0)
	{
		if (!args[1])
			return ;
		printf("%s", args[1]);
		return ;
	}
	printf("%s\n", args[0]);
}

int	builtin_cd(t_ms *ms, char *dir)
{
	if (chdir(dir) == -1)
		return (0);
	if (!set_cwd(ms))
		return (0);
	return (1);
}
