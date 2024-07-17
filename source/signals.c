/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:53:10 by atorma            #+#    #+#             */
/*   Updated: 2024/07/15 16:24:17 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

static void set_signal_exit(t_ms *ms)
{
	static t_ms *ms_struct;

	if (!ms)
	{
		ms_struct->exit_code = 130;
		ms_struct->stop_heredoc = 1;
	}
	else
		ms_struct = ms;
}

void	sig_handler_heredoc(int signo)
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

int event(void)
{
	return (0);
}

void	set_signals_heredoc(void)
{
	rl_event_hook = event;
	signal(SIGINT, sig_handler_heredoc);
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

int	set_signals_parent(t_ms *ms)
{
	struct sigaction sa;

	set_signal_exit(ms);

	rl_done = 0;
	rl_event_hook = NULL;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sig_parent_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (0);
	return (1);
}
