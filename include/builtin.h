/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:22:42 by atorma            #+#    #+#             */
/*   Updated: 2024/07/15 16:44:33 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

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

int		is_builtin(char	*cmd);
int		builtin_cd(t_ms *ms, char **args, char *dir);
int		builtin_exit(t_ms *ms, char **args);
void	builtin_echo(char **args);
int		builtin_env(t_ms *ms, int id, char **args);

#endif
