/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:57:24 by atorma            #+#    #+#             */
/*   Updated: 2024/06/26 20:36:40 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/environment.h"

int	set_cwd(t_ms *ms)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
		return (0);
	if (!env_var_set(ms, "PWD", dir))
	{
		free(dir);
		return (0);
	}
	if (ms->cwd && !env_var_set(ms, "OLDPWD", ms->cwd))
	{
		free(dir);
		return (0);
	}
	ms->cwd = env_var_get(ms->env, "PWD");
	free(dir);
	return (1);
}
