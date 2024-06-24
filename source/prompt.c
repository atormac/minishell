/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:14 by atorma            #+#    #+#             */
/*   Updated: 2024/06/24 16:27:15 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	prompt_set(t_ms *ms, char *prompt, size_t size)
{
	char	*username;

	ft_bzero(prompt, size);
	username = getenv("USER");
	if (!username)
		username = "unknown";
	ft_strlcat(prompt, username, size);
	ft_strlcat(prompt, "@", size);
	ft_strlcat(prompt, "minishell ", size);
	ft_strlcat(prompt, ms->cwd, size);
	ft_strlcat(prompt, "$ ", size);
}
