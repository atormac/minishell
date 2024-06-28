/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:12:21 by atorma            #+#    #+#             */
/*   Updated: 2024/06/28 17:14:27 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	*pipes_init(int pipe_count)
{
	int	i;
	int	*pipes;

	i = 0;
	pipes = malloc((pipe_count - 1) * (2 * sizeof(int)));
	if (!pipes)
		return (NULL);
	while (pipes && i < (pipe_count - 1))
	{
		if (pipe(pipes + (i * 2)) < 0)
		{
			i--;
			while (i >= 0)
			{
				close(pipes[i * 2]);
				close(pipes[i * 2 + 1]);
				i--;
			}
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	pipes_close(int *pipes, int pipe_count)
{
	int	i;
	int	*pipefd;

	i = 0;
	if (!pipes)
		return ;
	while (i < pipe_count)
	{
		pipefd = pipes + (i * 2);
		close(pipefd[0]);
		close(pipefd[1]);
		i++;
	}
	free(pipes);
}
