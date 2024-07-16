/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:59:03 by atorma            #+#    #+#             */
/*   Updated: 2024/07/15 19:43:46 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

char	**env_clone(char **envp);
void	env_sort(char **env);
void	env_print(char **env);
char	*env_var_get(char **env, char *var);
void	env_var_unset(char **env, char *var);
int		env_var_set(t_ms *ms, char *var, char *val);
int		env_update_shlvl(t_ms *ms);
int		env_set_cwd(t_ms *ms);
int		env_update_cwd(t_ms *ms);

#endif
