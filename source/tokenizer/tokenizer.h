/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:36:42 by lopoka            #+#    #+#             */
/*   Updated: 2024/06/25 19:55:33 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
#include <stdio.h>

typedef enum e_tkn_type
{
	t_cmnd,
	t_prnths_opn,
	t_prnths_cls,
	t_lwr,
	t_bgr,
	t_lwrlwr,
	t_bgrbgr,
	t_and,
	t_pipe
}	t_tkn_type;

typedef struct s_tkn
{
	int				type;
	char 			*str;
}	t_tkn;

typedef struct s_tkn_arr
{
	t_tkn	*arr;
	size_t	size;
	size_t	i;
	size_t	to_add;
	size_t	err;
}	t_tkn_arr;

//void	*ft_realloc(void *src, size_t old_s, size_t add_s);
//void	ft_tkn_arr_realloc(t_tkn_arr *tkn_arr);
void	ft_tkns_realloc(t_tkn_arr *tkns);
void	ft_free_tkns(t_tkn_arr *tkns);

