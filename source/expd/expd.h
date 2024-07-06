/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:25:15 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/06 11:53:41 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPD_H
# define EXPD_H

typedef struct s_token
{
	const char	*start;
	const char	*end;
}	t_token;

// 1st Expansion stage top level functions
void	ft_expd_ast(t_ms *ms, t_ast *ast);
void	expd_prep(t_ms *ms, t_ast *ast);

// Four expansion cases
void	ft_expd_rglr(char **res, char *s, size_t *i);
void	ft_expd_sq(char **res, char *s, size_t *i);
void	ft_expd_dq(char **res, char *s, size_t *i, t_ms *ms);
void	ft_expd_dlr(char **res, char *s, size_t *i, t_ms *ms);

// 2nd Expansion stage top level functions
void	ft_rm_empty_substrs(char *s);
char	**ft_expd_split_sub(const char *str, char sep, int esc);

// Utils
void	ft_free_null(char **s);
void	ft_rm_char(char *s, char c);
char	**ft_free_split(char **arr, int i);
#endif
