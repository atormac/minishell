/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:36:13 by atorma            #+#    #+#             */
/*   Updated: 2024/07/05 19:51:39 by atorma           ###   ########.fr       */
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
	int				is_first_cmd;
	int				pipe_read;
	int				pipe_write;
	int				mid_pipe_read;
	int				mid_pipe_write;
	int				cmd_error;
	int				exit_code;
	struct s_tkns	*tkns;
	int				prsr_err;
}	t_ms;

#include "environment.h"
#include "../source/tkns/tkns.h"
#include "../source/prsr/prsr.h"
#include "../source/expd/expd.h"

int		check_cmd(char *cmd);
void	error_print(char *s, char *error_str);
void	error_builtin(char *builtin, char *s, char *error_str);
char	**get_args(char *str);
size_t	args_count(char **args);
int		set_shlvl(t_ms *ms);
int		set_cwd(t_ms *ms);
int		update_cwd(t_ms *ms);
void	prompt_update(t_ms *ms, char *prompt, size_t size);
char	*path_join(char *path, char *bin);
char	**path_get(char **envp);
char	*path_find_bin(t_ms *ms, char *cmd);
int		exec_cmd(t_ms *ms, char *cmd, char **args);
int		is_executable(char *path);
int		init_signals(t_ms *ms);

#endif
