#include "../../include/minishell.h"
#include "../../include/signals.h"

int	minishell_init(t_ms *ms, char **envp)
{
	ms->do_exit = 0;
	ms->exit_code = 0;
	ms->abort = 0;
	ms->pipe[0] = -1;
	ms->pipe[1] = -1;
	ms->fd_heredoc = -1;
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
	minishell_close(ms->pipe);
}
