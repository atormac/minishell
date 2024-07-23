/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:08 by atorma            #+#    #+#             */
/*   Updated: 2024/07/23 16:31:25 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/environment.h"
#include "../include/builtin.h"

#include <readline/readline.h>
#include <readline/history.h>

void	commands_wait(t_ms *ms, t_ast *ast, t_ast *limit);
void	commands_exec(t_ms *ms, t_ast *ast, t_ast *prev);

static int	parse_line(t_ms *ms, char *line)
{
	ms->prsr_err = 0;
	ft_get_tokens(ms, line);
	//printf("ms->prsr_err %d\n", ms->prsr_err);
	ft_prsr(ms);
	//printf("ms->prsr_err %d\n", ms->prsr_err);
	if (ms->prsr_err)
		return (ft_prsr_err(ms), 0);
	ft_free_tkns(ms);
	ft_expd_ast(ms, ms->ast);
	if (ms->prsr_err)
		return (ft_free_ast(ms->ast), 0);
	return (1);
}

static void	process_line(t_ms *ms, char **line)
{
	ms->abort = 0;
	ms->stop_heredoc = 0;
	minishell_close(ms->pipe);
	if (!parse_line(ms, *line))
	{
		if (ms->prsr_err == e_mem)
			ms->abort = 1;
		return ;
	}
	free(*line);
	*line = NULL;
	commands_exec(ms, ms->ast, ms->ast);
	commands_wait(ms, ms->ast, NULL);
	ms->exit_code = ms->exit_code & 0377;
	ft_free_ast(ms->ast);
	ms->ast = NULL;
}

static	void	minishell(t_ms *ms)
{
	char	prompt[1024];
	char	*line;

	while (!ms->do_exit && !ms->abort)
	{
		prompt_update(ms, prompt, sizeof(prompt));
		line = readline(prompt);
		if (line == NULL)
			break ;
		if (*line)
		{
			add_history(line);
			process_line(ms, &line);
		}
		free(line);
		line = NULL;
	}
	if (!ms->do_exit && !ms->abort)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	free(line);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	(void)argc;
	(void)argv;
	if (!minishell_init(&ms, envp))
	{
		ft_putstr_fd("Error initializing minishell\n", STDERR_FILENO);
		minishell_cleanup(&ms);
		return (EXIT_FAILURE);
	}
	minishell(&ms);
	if (ms.abort)
	{
		ft_putstr_fd("Aborted, critical error encountered\n", STDERR_FILENO);
		ms.exit_code = EXIT_FAILURE;
	}
	minishell_cleanup(&ms);
	return (ms.exit_code);
}
