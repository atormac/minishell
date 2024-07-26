/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:45:30 by atorma            #+#    #+#             */
/*   Updated: 2024/07/26 16:46:39 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <fcntl.h>

int	std_save(t_ms *ms)
{
	ms->std[0] = dup(STDIN_FILENO);
	ms->std[1] = dup(STDOUT_FILENO);
	if (ms->std[0] == -1 || ms->std[1] == -1)
	{
		ms->abort = 1;
		return (0);
	}
	return (1);
}

int	std_reset(t_ms *ms)
{
	if (dup2(ms->std[0], 0) < 0 || dup2(ms->std[1], 1) < 0)
	{
		ms->abort = 1;
		return (0);
	}
	close(ms->std[0]);
	close(ms->std[1]);
	ms->std[0] = -1;
	ms->std[1] = -1;
	return (1);
}
