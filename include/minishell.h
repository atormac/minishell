/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:36:13 by atorma            #+#    #+#             */
/*   Updated: 2024/06/20 15:37:00 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"

typedef struct t_ms
{
	char	**envp;
	char	**path;
	int		fd_in;
	int		fd_out;
	int		exit_code;
}	t_ms;

char	*path_join(char *path, char *bin);
char	**path_get(char **envp);
int		is_builtin(char	*cmd);

#endif
