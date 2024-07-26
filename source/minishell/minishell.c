/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:42:50 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/26 16:06:35 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
#include "../../include/signals.h"

int	minishell_init(t_ms *ms, char **envp)
{
	ms->is_parent = 1;
	ms->tkns = NULL;
	ms->ast = NULL;
	ms->do_exit = 0;
	ms->exit_code = 0;
	ms->abort = 0;
	ft_memset(ms->pipe, -1, sizeof(ms->pipe));
	ft_memset(ms->std, -1, sizeof(ms->std));
	ms->prsr_err = 0;
	ms->cwd = NULL;
	ms->env = NULL;
	ms->env = env_clone(envp);
	if (!ms->env)
		return (0);
	if (!env_update_shlvl(ms))
		return (0);
	if (!env_set_cwd(ms))
		return (0);
	if (!set_signals(ms, SIGNALS_PARENT))
		return (0);
	return (1);
}

void	minishell_close(int *fd)
{
	if (!fd)
		return ;
	if (fd[0] >= 0)
		close(fd[0]);
	if (fd[1] >= 0)
		close(fd[1]);
	fd[0] = -1;
	fd[1] = -1;
}

void	minishell_cleanup(t_ms *ms)
{
	free_array(ms->env);
	free(ms->cwd);
	if (ms->tkns)
		ft_free_tkns(ms);
	if (ms->ast)
		ft_free_ast(ms->ast);
	minishell_close(ms->pipe);
	minishell_close(ms->std);
}
