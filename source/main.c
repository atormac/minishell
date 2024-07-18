/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:08 by atorma            #+#    #+#             */
/*   Updated: 2024/07/17 21:31:25 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/environment.h"
#include "../include/builtin.h"

#include <readline/readline.h>
#include <readline/history.h>

void	commands_wait(t_ms *ms, t_ast *ast, t_ast *limit);
void	commands_exec(t_ms *ms, t_ast *ast, t_ast *prev);
void	ft_free_ast(t_ast *ast);
t_ast	*ft_prsr(t_tkns *tkns, t_ms *ms);
t_ast	*ft_get_ast(t_tkns *tkns, int tree_top, t_ms *ms);
void	ft_expd_ast(t_ms *ms, t_ast *ast);

static int	parse_line(t_ms *ms, t_ast **ast, char *line)
{
	ft_get_tokens(ms, line);
	if (!ms->tkns)
		return (0);
	*ast = ft_prsr(ms->tkns, ms);
	if (ms->prsr_err)
	{
		ft_prsr_err(ms, *ast);
		return (0);
	}	
	ft_free_tkns(ms);
	ft_expd_ast(ms, *ast);
	if (ms->prsr_err)
	{
		ft_free_ast(*ast);
		return (0);
	}
	return (1);
}

static void	process_line(t_ms *ms, char **line)
{
	t_ast	*ast;

	ms->abort = 0;
	ms->stop_heredoc = 0;
	minishell_close(ms->pipe);
	if (!parse_line(ms, &ast, *line))
		return ;
	free(*line);
	*line = NULL;
	commands_exec(ms, ast, ast);
	commands_wait(ms, ast, NULL);
	ms->exit_code = ms->exit_code & 0377; //Magic
	ft_free_ast(ast);
}

static	void	minishell(t_ms *ms)
{
	char	prompt[1024];
	char	*line;

	while (1)
	{
		prompt_update(ms, prompt, sizeof(prompt));
		line = readline(prompt);
		if (line == NULL)
			break;
		if (*line)
		{
			add_history(line);
			process_line(ms, &line);
		}
		free(line);
		line = NULL;
		if (ms->do_exit)
			break;
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

/*
//Parser testing main
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
		free_array(ms.env);
		free(ms.cwd);
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
	if (ms.prsr_err == 2)
		printf("Error %d, current: %ld, token type: %d\n", ms.prsr_err, ms.tkns->curr_tkn - 1, ms.tkns->arr[ms.tkns->curr_tkn - 1].type);
	if (ast)
	{
		printf("\nPRE EXPANSION\n");
		ft_print_ast(&ms, ast, 0);
		//--------------------
		ft_expd_ast(&ms, ast);
		if (ms.prsr_err)
			ft_free_ast(ast);
		//--------------------
		printf("\nEXPANDED\n");
		ft_print_ast(&ms, ast, 1);
		
		ft_free_ast(ast);
	}
	if (ms.tkns)
		ft_free_tkns(&ms);
	free_array(ms.env);
	free(ms.cwd);
	return (0);
}*/
