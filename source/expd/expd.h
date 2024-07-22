/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:25:15 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/22 14:45:46 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPD_H
# define EXPD_H

# include <dirent.h>

// 1st Expansion stage top level functions
char	*ft_expd_heredoc(char *s, t_ms *ms);
void	ft_expd_ast(t_ms *ms, t_ast *ast);
void	expd_prep(t_ms *ms, t_ast *ast);

// Four expansion cases
void	ft_expd_rglr(char **res, char *s, size_t *i);
void	ft_expd_rglr_hrdc(char **res, char *s, size_t *i);
void	ft_expd_sq(char **res, char *s, size_t *i);
void	ft_expd_dq(char **res, char *s, size_t *i, t_ms *ms);
void	ft_expd_dlr(char **res, char *s, size_t *i, t_ms *ms);
void	ft_expd_dlr_sub(char **res, char *s, size_t *i, t_ms *ms);
void	ft_expd_tld(char **res, size_t *i, t_ms *ms);

// 2nd Expansion stage top level functions
void	ft_rm_empty_substrs(char *s);
char	**ft_expd_split_sub(const char *str, char sep);

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
