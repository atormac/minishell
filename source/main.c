/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:08 by atorma            #+#    #+#             */
/*   Updated: 2024/06/26 14:39:28 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

static void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static	int	minishell_init(t_ms *ms, char **envp)
{
	ms->exit_code = 0;
	ms->env = NULL;
	if (envp)
	{
		ms->env = env_clone(envp);
		if (!ms->env)
		{
			printf("Failed to initialize env\n");
			return (0);
		}
	}
	ms->cwd = env_var_get(ms->env, "PWD");
	env_print(ms->env);
	printf("ms->cwd: %s\n", ms->cwd);
	printf("minishell initialized\n");
	return (1);
}

void	minishell_cleanup(t_ms *ms)
{
	free_array(ms->env);
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
	free(line);
}

int main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	(void)argc;
	(void)argv;
	if (!minishell_init(&ms, envp))
	{
		ft_putstr_fd("Error initializing minishell\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	minishell(&ms);
	minishell_cleanup(&ms);
	return (ms.exit_code);
}
