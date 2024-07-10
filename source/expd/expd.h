/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:25:15 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/10 14:36:35 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPD_H
# define EXPD_H

# include <dirent.h>

typedef struct s_token
{
	const char	*start;
	const char	*end;
}	t_token;

typedef struct s_glbr
{
	char	**arr;
	size_t	size;
	size_t	curr;
	size_t	i;
	size_t	to_add;
}	t_glbr;

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

// 3rd Expansion stage top level function
int		ft_wldcrd(char *s, char *ptrn);
char	**ft_glbr(char **expd);
void	ft_init_glbr(t_glbr *glbr);
void	ft_glbr_realloc(t_glbr *glbr);
void	ft_glbr_add(t_glbr *glbr, char *s);
void	ft_free_glbr(t_glbr *glbr);
void	ft_strip_qtes(char *s);

// Utils
void	ft_free_null(char **s);
void	ft_free_split_null(char **arr);
void	ft_rm_char(char *s, char c);
char	**ft_free_split(char **arr, int i);
#endif
