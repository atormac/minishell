/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:36:13 by atorma            #+#    #+#             */
/*   Updated: 2024/07/19 13:12:58 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"
# include "../libft/libft.h"
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <unistd.h>
# include "environment.h"
# include "../source/tkns/tkns.h"
# include "../source/prsr/prsr.h"
# include "../source/expd/expd.h"

int		minishell_init(t_ms *ms, char **envp);
void	minishell_close(int *fd);
void	minishell_cleanup(t_ms *ms);
int		check_cmd(char *cmd);
void	error_print(char *s, char *error_str);
void	error_builtin(char *builtin, char *s, char *error_str);
size_t	args_count(char **args);
void	prompt_update(t_ms *ms, char *prompt, size_t size);
int		is_executable(char *path);

#endif
