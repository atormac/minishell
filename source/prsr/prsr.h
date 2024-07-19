/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsr.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:30:53 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/19 23:33:17 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRSR_H
# define PRSR_H

//Top level functions
void	ft_prsr(t_ms *ms);
t_ast	*ft_get_ast(t_tkns *tkns, int tree_top, t_ms *ms);
t_ast	*ft_get_branch(t_tkns *tkns, t_ms *ms);
t_ast	*ft_merge_branch(t_ast *ast, int op, t_ast *new_branch, t_ms *ms);

//Cmnd node
t_ast	*ft_get_cmnd(t_tkns *tkns, t_ms *ms);
int		ft_join_cmnd(t_tkns *tkns, t_ast *cmnd_node);
char	*ft_strjoin_space(char *s1, char *s2);

//Io node
int		ft_get_io(t_tkns *tkns, t_ast *cmnd_node, t_ms *ms);
void	ft_add_io_node(t_ast *cmnd_node, t_ast *io_node);

//Token type checkers
int		ft_is_tkn(t_tkns *tkns);
int		ft_is_tkn_bop(t_tkns *tkns);
int		ft_is_tkn_io(t_tkns *tkns);
int		ft_is_tkn_cmnd(t_tkns *tkns);

//Ast memory handling
t_ast	*ft_get_ast_node(int type);
void	ft_free_ast(t_ast *ast);

//Ast errors
void	ft_set_prsr_err(t_ms *ms, int type);
void	ft_prsr_err(t_ms *ms);

//Ast print
void	ft_print_ast(t_ms *ms, t_ast *ast, int expd);

#endif
