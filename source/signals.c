/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:53:10 by atorma            #+#    #+#             */
/*   Updated: 2024/07/15 14:56:47 by atorma           ###   ########.fr       */
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
		ms_struct->exit_code = 130;
	else
		ms_struct = ms;
}

static void	sig_parent_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		set_signal_exit(NULL);
	}
}

int	init_signals(t_ms *ms)
{
	struct sigaction sa;

	set_signal_exit(ms);

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sig_parent_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (0);
	return (1);
}
