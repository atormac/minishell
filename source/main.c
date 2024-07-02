/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:27:08 by atorma            #+#    #+#             */
/*   Updated: 2024/07/02 18:13:41 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/environment.h"
#include "../include/builtin.h"

#include <readline/readline.h>
#include <readline/history.h>

/*static	int	minishell_init(t_ms *ms, char **envp)
{
	ms->exit_code = 0;
	ms->cmd_error = 0;
	ms->prsr_err = 0;
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
}*/

void	minishell_cleanup(t_ms *ms)
{
	free_array(ms->env);
	free(ms->cwd);
}
void	ft_free_ast(t_ast *ast);
t_ast	*ft_get_ast(t_tkns *tkns, int tree_top, t_ms *ms);

void	recurse_ast(t_ms *ms, t_ast *ast)
{
	t_ast *curr;

	if (!ast)
		return ;
	if (ast->str)
		printf("Ast type %d, str %s ", ast->type, ast->str);
	curr = ast->io;
	while (curr)
	{
		printf(", IO type: %d, s: %s ", curr->type, curr->str);
		curr = curr->io;
	}
	//Process ast entry here
	//Do redirection if needed
	//exec_cmd if there is one
	if (ast->str)
		exec_cmd(ms, ast->str + 1, NULL);
	if (ast->left)
		recurse_ast(ms, ast->left);
	if (ast->right)
		recurse_ast(ms, ast->right);
}

void	process_line(t_ms *ms, char *line)
{
	ft_get_tokens(ms, line);
	if (!ms->tkns)
		return ;
	printf("--------------TOKENS----------------\n");
	for (size_t i = 0; i < ms->tkns->i; i++)
	{
		ft_printf("Type %d str %s\n", ms->tkns->arr[i].type, ms->tkns->arr[i].str);
	}

	printf("------------AST-------------- i=%ld curr=%ld\n", ms->tkns->i, ms->tkns->curr_tkn);
	t_ast *ast = ft_get_ast(ms->tkns, 1, ms);
	if (!ast)
		return ;
	ft_print_ast(ast);
	ft_free_ast(ast);
	ft_free_tkns(ms);
}

/*static	void	minishell(t_ms *ms)
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
int main(int argc, char **argv)
{
	
	(void) argc;
	t_ms ms;
	ms.prsr_err = 0;
	char *line = argv[1];

	ft_get_tokens(&ms, line);
	printf("--------------TOKENS----------------\n");
	for (size_t i = 0; i < ms.tkns->i; i++)
	{
		ft_printf("Type %d str |%s|\n", ms.tkns->arr[i].type, ms.tkns->arr[i].str);
	}

	printf("------------AST-------------- i=%ld curr=%ld\n", ms.tkns->i, ms.tkns->curr_tkn);
	t_ast *ast = ft_get_ast(ms.tkns, 1, &ms);
	if (ast)
		ft_print_ast(ast);
	printf("Error %d\n", ms.prsr_err);
	ft_free_ast(ast);
	ft_free_tkns(&ms);
}
