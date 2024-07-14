/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:14 by atorma            #+#    #+#             */
/*   Updated: 2024/07/14 15:05:35 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/environment.h"

static void	prompt_set_dir(t_ms *ms, char *prompt, size_t size)
{
	char	*home_dir;
	size_t	home_len;

	home_dir = env_var_get(ms->env, "HOME");
	if (home_dir && ft_strncmp(ms->cwd, home_dir, ft_strlen(home_dir)) == 0)
	{
		home_len = ft_strlen(home_dir);
		if (ms->cwd[home_len] == '\0' || ms->cwd[home_len] == '/')
		{
			ft_strlcat(prompt, "~", size);
			ft_strlcat(prompt, ms->cwd + ft_strlen(home_dir), size);
			return	;
		}
	}
	ft_strlcat(prompt, ms->cwd, size);
}

void	prompt_update(t_ms *ms, char *prompt, size_t size)
{
	char	*username;

	ft_bzero(prompt, size);
	username = env_var_get(ms->env, "USER");
	if (!username)
		username = "unknown";
	ft_strlcat(prompt, username, size);
	ft_strlcat(prompt, "@", size);
	ft_strlcat(prompt, "minishell:", size);
	prompt_set_dir(ms, prompt, size);
	ft_strlcat(prompt, "$ ", size);
}
