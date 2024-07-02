/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:36:13 by atorma            #+#    #+#             */
/*   Updated: 2024/07/02 13:50:47 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <string.h>
#include <errno.h>
#include <stdio.h>

typedef struct t_ms
{
	char			**env;
	char			**path;
	char			*cwd;
	int				cmd_error;
	int				exit_code;
	struct s_tkns	*tkns;
	int				prsr_err;
}	t_ms;

#include "../source/tokenizer/tokenizer.h"

char	**get_args(char **cmd);
size_t	args_count(char **args);
void	set_shlvl(t_ms *ms);
int		set_cwd(t_ms *ms);
int		update_cwd(t_ms *ms);
void	prompt_update(t_ms *ms, char *prompt, size_t size);
char	*path_join(char *path, char *bin);
char	**path_get(char **envp);
char	*path_find_bin(t_ms *ms, char *cmd);
int		exec_cmd(t_ms *ms, char *cmd, char **args);
int		is_executable(char *path);
int		init_signals(void);

#endif
