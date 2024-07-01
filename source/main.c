/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:08 by atorma            #+#    #+#             */
/*   Updated: 2024/07/01 18:37:02 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/environment.h"
#include "../include/builtin.h"

#include <readline/readline.h>
#include <readline/history.h>

static	int	minishell_init(t_ms *ms, char **envp)
{
	ms->exit_code = 0;
	ms->cmd_error = 0;
	ms->cwd = NULL;
	ms->env = NULL;
	if (envp)
	{
		ms->env = env_clone(envp);
		if (!ms->env)
		{
			printf("Failed to initialize env\n");
			return (0);
		}
		set_shlvl(ms);
	}
	if (!set_cwd(ms))
		return (0);
	if (!init_signals())
		return (0);
	return (1);
}

void	minishell_cleanup(t_ms *ms)
{
	free_array(ms->env);
	free(ms->cwd);
}
void	ft_free_ast(t_ast *ast);
t_ast	*ft_get_ast(t_tkns *tkns, int tree_top);

void	recurse_ast(t_ms *ms, t_ast *ast, t_ast *prev)
{
	//t_ast *curr;

	if (!ast)
		return ;
	if (prev->type == 5)
	{
		if (ast->str)
		{
			printf("pipe: type %d, cmd %s\n", ast->type, ast->str);
			if (ast->io)
				printf("io->str: %s, type: %d\n", ast->io->str, ast->io->type);
		}
	}
	else
	{
		if (ast->str)
		{
			printf("no pipe: type %d, cmd %s\n", ast->type, ast->str);
			if (ast->io)
				printf("io->str: %s, type: %d\n", ast->io->str, ast->io->type);
		}
	}
	/*
	curr = ast->io;
	while (curr)
	{
		printf(", IO type: %d, s: %s ", curr->type, curr->str);
		curr = curr->io;
	}
	*/
	//Process ast entry here
	//Do redirection if needed
	//exec_cmd if there is one
	/*
	if (ast->str)
	{
		printf("\n");
		exec_cmd(ms, ast->str + 1, NULL);
	}
	*/
	if (ast->left)
		recurse_ast(ms, ast->left, ast);
	if (ast->right)
		recurse_ast(ms, ast->right, ast);
}

void	process_line(t_ms *ms, char *line)
{
	ft_get_tokens(ms, line);
	if (!ms->tkns)
		return ;
	t_ast *ast = ft_get_ast(ms->tkns, 1);
	if (!ast)
		return ;
	recurse_ast(ms, ast, ast);
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
