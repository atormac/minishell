/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:36:42 by lopoka            #+#    #+#             */
/*   Updated: 2024/06/27 15:17:52 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../../include/minishell.h"

typedef enum e_tkn_type
{
	t_cmnd,
	t_prnths_opn,
	t_prnths_cls,
	t_lwr,
	t_bgr,
	t_pipe,
	t_lwrlwr,
	t_bgrbgr,
	t_or,
	t_and
}	t_tkn_type;

typedef struct s_tkn
{
	t_tkn_type		type;
	char			*str;
}	t_tkn;

typedef struct s_tkns
{
	t_tkn	*arr;
	size_t	size;
	size_t	curr_tkn;
	size_t	i;
	size_t	to_add;
	size_t	err;
}	t_tkns;

//Tkns
t_tkns	ft_get_tokens(char *line);

//Tkns utils
int		ft_is_quote(char *c);
char	*ft_quote_end(char *line);
int		ft_is_whitespace(char *c);
char	*ft_skip_whitespace(char **str);
int		ft_is_operator(char *str);

//Tkns memory handling
void	ft_tkns_realloc(t_tkns *tkns);
void	ft_free_tkns(t_tkns *tkns);

#endif
