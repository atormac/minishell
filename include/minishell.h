/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:36:13 by atorma            #+#    #+#             */
/*   Updated: 2024/06/26 20:36:05 by atorma           ###   ########.fr       */
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
	char	**env;
	char	**path;
	char	*cwd;
	int		cmd_error;
	int		exit_code;
}	t_ms;


char	**get_args(char **cmd);
size_t	args_count(char **args);
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
