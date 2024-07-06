/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:08 by atorma            #+#    #+#             */
/*   Updated: 2024/07/06 12:20:02 by lopoka           ###   ########.fr       */
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
}

void	ft_free_ast(t_ast *ast);
t_ast	*ft_prsr(t_tkns *tkns, t_ms *ms);
t_ast	*ft_get_ast(t_tkns *tkns, int tree_top, t_ms *ms);
int		exec_ast(t_ms *ms, t_ast *ast, int cmd_id);
int		pid_wait(pid_t pid);
void	ft_expd_ast(t_ms *ms, t_ast *ast);

void	recurse_ast(t_ms *ms, t_ast *ast, t_ast *prev)
{
	int	cmd_id;

	if (ast->type == 0)
		ast->pid = -1;
	if (ast->str && prev->type == 5)
	{
		if (ms->is_first_cmd)
		{
			cmd_id = CMD_FIRST;
			ms->is_first_cmd = 0;
		}
		else if (prev->right == ast && !ast->left && !ast->right)
			cmd_id = CMD_LAST;
		else
			cmd_id = CMD_MIDDLE;
		exec_ast(ms, ast, cmd_id);
	}
	else if (ast->str)
		exec_ast(ms, ast, CMD_NOPIPE);
	if (ast->left)
		recurse_ast(ms, ast->left, ast);
	if (ast->right)
		recurse_ast(ms, ast->right, ast);
}

void	wait_ast(t_ms *ms, t_ast *ast)
{
	if (ast->type == 0 && ast->pid >= 0)
		ms->exit_code = pid_wait(ast->pid);
	if (ast->left)
		wait_ast(ms, ast->left);
	if (ast->right)
		wait_ast(ms, ast->right);
}

void	process_line(t_ms *ms, char *line)
{
	ms->is_first_cmd = 1;
	ms->pipe_read = -1;
	ms->pipe_write = -1;
	ft_get_tokens(ms, line);
	if (!ms->tkns)
		return ;
	t_ast *ast = ft_get_ast(ms->tkns, 1, ms);
	if (!ast)
		return ;
	ft_expd_ast(ms, ast);
	recurse_ast(ms, ast, ast);
	wait_ast(ms, ast);
	
	//ft_print_ast(ms, ast);
	ft_free_ast(ast);
	ft_free_tkns(ms);
}
/*
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
*/

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
		return (1);
	printf("--------------TOKENS----------------\n");
	for (size_t i = 0; i < ms.tkns->i; i++)
	{
		ft_printf("Type %d str |%s|\n", ms.tkns->arr[i].type, ms.tkns->arr[i].str);
	}

	printf("------------AST-------------- i=%ld curr=%ld\n", ms.tkns->i, ms.tkns->curr_tkn);
	t_ast *ast = ft_prsr(ms.tkns, &ms);
	printf("----------AST Error %d-----------------\n", ms.prsr_err);
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
