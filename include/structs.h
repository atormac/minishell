/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:08:25 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/19 13:27:56 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdlib.h>

// Tkns
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
}	t_tkns;

// Prsr
typedef struct s_ast
{
	int				type;
	int				pid;
	char			*str;
	char			**expd_str;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*io;
}	t_ast;

typedef enum e_prsr_err
{
	e_none,
	e_mem,
	e_sntx
}	t_prsr_err;

// Expd
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

// Main
enum
{
	CMD_NOPIPE,
	CMD_FIRST,
	CMD_MIDDLE,
	CMD_LAST
};

typedef struct t_ms
{
	char			**env;
	char			**path;
	char			*cwd;
	int				abort;
	int				pipe[2];
	int				fd_heredoc;
	int				stop_heredoc;
	int				exit_code;
	int				do_exit;
	struct s_tkns	*tkns;
	int				prsr_err;
}	t_ms;

#endif
