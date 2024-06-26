/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:57:24 by atorma            #+#    #+#             */
/*   Updated: 2024/06/26 17:57:43 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_cwd(t_ms *ms)
{
	char	tmp[1024];

	if (!getcwd(tmp, sizeof(tmp)))
		return (0);
	if (!env_var_set(ms, "PWD", tmp))
		return (0);
	ms->cwd = env_var_get(ms->env, "PWD");
	return (1);
}