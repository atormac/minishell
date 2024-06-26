/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:36:13 by atorma            #+#    #+#             */
/*   Updated: 2024/06/26 18:06:35 by atorma           ###   ########.fr       */
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
	int		exit_code;
}	t_ms;

enum
{
	BUILTIN_NONE,
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT
};

int		set_cwd(t_ms *ms);
char	**env_clone(char **envp);
void	env_print(char **env);
char	*env_var_get(char **env, char *var);
void	env_var_unset(char **env, char *var);
int		env_var_set(t_ms *ms, char *var, char *val);
void	prompt_set(t_ms *ms, char *prompt, size_t size);
char	*path_join(char *path, char *bin);
char	**path_get(char **envp);
char	*path_find_bin(t_ms *ms, char *cmd);
int		is_builtin(char	*cmd);
int		builtin_cd(t_ms *ms, char *dir);
void	builtin_echo(char **args);
int		exec_cmd(t_ms *ms, char *cmd, char **args);

#endif
