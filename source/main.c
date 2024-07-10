/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:08 by atorma            #+#    #+#             */
/*   Updated: 2024/07/10 16:59:54 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/environment.h"
#include "../include/builtin.h"

#include <readline/readline.h>
#include <readline/history.h>

void	commands_wait(t_ms *ms, t_ast *ast);
void	commands_exec(t_ms *ms, t_ast *ast, t_ast *prev);
void	ft_free_ast(t_ast *ast);
t_ast	*ft_prsr(t_tkns *tkns, t_ms *ms);
t_ast	*ft_get_ast(t_tkns *tkns, int tree_top, t_ms *ms);
void	ft_expd_ast(t_ms *ms, t_ast *ast);

static	int	minishell_init(t_ms *ms, char **envp)
{
	ms->exit_code = 0;
	ms->cmd_error = 0;
	ms->fd_heredoc = -1;
	ms->prsr_err = 0;
	ms->cwd = NULL;
	ms->env = NULL;
	ms->env = env_clone(envp);
	if (!ms->env)
		return (0);
	if (!set_shlvl(ms))
		return (0);
	if (!set_cwd(ms))
		return (0);
	if (!init_signals(ms))
		return (0);
	return (1);
}

void	minishell_cleanup(t_ms *ms)
{
	free_array(ms->env);
	free(ms->cwd);
	if (ms->pipe_read >= 0)
		close(ms->pipe_read);
	if (ms->pipe_write >= 0)
		close(ms->pipe_read);
}

static void	process_line(t_ms *ms, char *line)
{
	t_ast	*ast;

	ms->cmd_error = 0;
	ms->pipe_read = -1;
	ms->pipe_write = -1;
	ft_get_tokens(ms, line);
	if (!ms->tkns)
		return ;
	ast = ft_prsr(ms->tkns, ms);
	if (ast)
	{
		ft_expd_ast(ms, ast);
		commands_exec(ms, ast, ast);
		commands_wait(ms, ast);
	}
	ft_free_ast(ast);
	ft_free_tkns(ms);
}

static	void	minishell(t_ms *ms)
{
	char	prompt[1024];
	char	*line;

	while (1)
	{
		prompt_update(ms, prompt, sizeof(prompt));
		line = readline(prompt);
		if (line == NULL || is_builtin(line) == BUILTIN_EXIT)
			break;
		if (*line)
		{
			add_history(line);
			process_line(ms, line);
		}
		free(line);
	}
	printf("exit\n");
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
		minishell_cleanup(&ms);
		return (EXIT_FAILURE);
	}
	minishell(&ms);
	minishell_cleanup(&ms);
	return (ms.exit_code);
}

//Parser testing main

/*

int main(int argc, char **argv, char **envp)
{
	
	(void) argc;
	t_ms ms;
	ms.prsr_err = 0;
	ms.tkns = 0;
	char *line = argv[1];

	if (!minishell_init(&ms, envp))
	{
		ft_putstr_fd("Error initializing minishell\n", STDERR_FILENO);
		minishell_cleanup(&ms);
		return (EXIT_FAILURE);
	}

	ft_get_tokens(&ms, line);
	if (!ms.tkns)
	{
		minishell_cleanup(&ms);
		return (1);
	}
	printf("--------------TOKENS----------------\n");
	for (size_t i = 0; i < ms.tkns->i; i++)
	{
		ft_printf("Type %d str |%s|\n", ms.tkns->arr[i].type, ms.tkns->arr[i].str);
	}

	printf("------------AST-------------- i=%ld curr=%ld\n", ms.tkns->i, ms.tkns->curr_tkn);
	t_ast *ast = ft_prsr(ms.tkns, &ms);
	printf("----------ast error %d-----------------\n", ms.prsr_err);
	if (ast)
	{
		ft_expd_ast(&ms, ast);
		ft_print_ast(&ms, ast);
		ft_free_ast(ast);
	}
	if (ms.tkns)
		ft_free_tkns(&ms);
	
	minishell_cleanup(&ms);

	return (0);
}
*/
