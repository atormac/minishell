/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:53:10 by atorma            #+#    #+#             */
/*   Updated: 2024/07/23 17:54:52 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/signals.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

int	event(void);

static void	set_signal_exit(t_ms *ms)
{
	static t_ms	*ms_struct;

	if (!ms)
	{
		ms_struct->exit_code = 130;
		ms_struct->stop_heredoc = 1;
	}
	else
		ms_struct = ms;
}

static void	sig_handler_heredoc(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_done = 1;
		set_signal_exit(NULL);
	}
}

static void	sig_parent_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		if (!isatty(STDIN_FILENO) || errno != EINTR)
			return ;
		set_signal_exit(NULL);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static int	set_parent(void)
{
	struct sigaction	sa;

	rl_done = 0;
	rl_event_hook = NULL;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sig_parent_handler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (0);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (0);
	return (1);
}

int	set_signals(t_ms *ms, int type)
{
	set_signal_exit(ms);
	ms->abort = 1;
	if (type == SIGNALS_PARENT)
	{
		if (!set_parent())
			return (0);
	}
	else if (type == SIGNALS_HEREDOC)
	{
		rl_event_hook = event;
		if (signal(SIGINT, sig_handler_heredoc) == SIG_ERR)
			return (0);
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			return (0);
	}
	else if (type == SIGNALS_DEFAULT)
	{
		if (signal(SIGINT, SIG_DFL) == SIG_ERR)
			return (0);
		if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
			return (0);
	}
	ms->abort = 0;
	return (1);
}
