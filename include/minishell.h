/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:36:13 by atorma            #+#    #+#             */
/*   Updated: 2024/06/25 17:58:50 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"

typedef struct t_ms
{
	char	**env;
	char	**path;
	char	*cwd;
	int		fd_in;
	int		fd_out;
	int		heredoc;
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

char	**env_clone(char **envp);
void	env_print(char **env);
char	*env_var_get(char **env, char *var);
void	env_var_remove(char **env, char *var);
int		env_var_set(t_ms *ms, char *var, char *val);
void	prompt_set(t_ms *ms, char *prompt, size_t size);
char	*path_join(char *path, char *bin);
char	**path_get(char **envp);
char	*path_find_bin(t_ms *ms, char *cmd);
int		is_builtin(char	*cmd);

#endif
