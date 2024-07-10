/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:36:13 by atorma            #+#    #+#             */
/*   Updated: 2024/07/10 15:12:36 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <unistd.h>

enum
{
	CMD_NOPIPE,
	CMD_FIRST,
	CMD_MIDDLE,
	CMD_LAST
};


typedef struct t_ms
{
	char			**env;
	char			**path;
	char			*cwd;
	int				pipe_read;
	int				pipe_write;
	int				fd_heredoc;
	int				cmd_error;
	int				exit_code;
	struct s_tkns	*tkns;
	int				prsr_err;
}	t_ms;

#include "environment.h"
#include "../source/tkns/tkns.h"
#include "../source/prsr/prsr.h"
#include "../source/expd/expd.h"

void	heredoc_unlink(void);
int		check_cmd(char *cmd);
void	error_print(char *s, char *error_str);
void	error_builtin(char *builtin, char *s, char *error_str);
size_t	args_count(char **args);
int		set_shlvl(t_ms *ms);
int		set_cwd(t_ms *ms);
int		update_cwd(t_ms *ms);
void	prompt_update(t_ms *ms, char *prompt, size_t size);
int		is_executable(char *path);
int		init_signals(t_ms *ms);

#endif
