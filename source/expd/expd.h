/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:25:15 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/04 20:39:24 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPD_H
# define EXPD_H

//Top level functions
void	ft_expd_ast(t_ms *ms, t_ast *ast);
char	*expd_prep(char *s, t_ms *ms);

//Four expansion cases
void	ft_expd_rglr(char **res, char *s, size_t *i);
void	ft_expd_sq(char **res, char *s, size_t *i);
void	ft_expd_dq(char **res, char *s, size_t *i, t_ms *ms);
void	ft_expd_dlr(char **res, char *s, size_t *i, t_ms *ms);

//Utils
void	ft_free_null(char **s);

#endif
