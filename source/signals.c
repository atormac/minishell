#include "../include/minishell.h"
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

int	init_signals(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (0);
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		return (0);
	return (1);
}
