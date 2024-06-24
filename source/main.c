/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:08 by atorma            #+#    #+#             */
/*   Updated: 2024/06/24 17:04:58 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

static	int	minishell_init(t_ms *ms, char **argv, char **envp)
{
	ms->envp = envp;
	ms->cwd = malloc(256);

	getcwd(ms->cwd, 256);

	printf("ms->cwd: %s\n", ms->cwd);
	printf("minishell initialized\n");
	(void)argv;
	return (1);
}

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static	void	minishell(t_ms *ms)
{
	char	prompt[1024];
	char	*line;

	signal(SIGINT, sig_handler);
	while (1)
	{
		prompt_set(ms, prompt, sizeof(prompt));
		line = readline(prompt);
		if (line == NULL || is_builtin(line) == BUILTIN_EXIT)
			break;
		if (*line)
		{
			add_history(line);
			printf("line: %s\n", line);
		}
		free(line);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	(void)argc;
	if (!minishell_init(&ms, argv, envp))
	{
		ft_putstr_fd("Error initializing minishell\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}

	minishell(&ms);
	return (0);
}
