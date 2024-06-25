/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:14 by atorma            #+#    #+#             */
/*   Updated: 2024/06/25 16:19:32 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	prompt_dir_set(t_ms *ms, char *prompt, size_t size)
{
	char	*home_dir;

	home_dir = env_var_get(ms->env, "HOME");
	if (home_dir && ft_strncmp(ms->cwd, home_dir, ft_strlen(home_dir)) == 0)
	{
		ft_strlcat(prompt, "~", size);
		ft_strlcat(prompt, ms->cwd + ft_strlen(home_dir), size);
		return	;
	}
	ft_strlcat(prompt, ms->cwd, size);
}

void	prompt_set(t_ms *ms, char *prompt, size_t size)
{
	char	*username;

	ft_bzero(prompt, size);
	username = env_var_get(ms->env, "USER");
	if (!username)
		username = "unknown";
	ft_strlcat(prompt, username, size);
	ft_strlcat(prompt, "@", size);
	ft_strlcat(prompt, "minishell ", size);
	prompt_dir_set(ms, prompt, size);
	ft_strlcat(prompt, "$ ", size);
}
