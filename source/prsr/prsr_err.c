/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsr_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:33:19 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/16 22:27:43 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_prsr_err(t_ms *ms, t_ast *ast)
{
	char	**tkns_arr;
	int		tkn_type;

	tkns_arr = (char *[]){"command", "(", ")", "<", ">", "|",
		"<<", ">>", "||", "&&", "newline"};
	if (ms->prsr_err == 2)
	{
		if (!ft_is_tkn(ms->tkns))
			tkn_type = 10;
		else
			tkn_type = ms->tkns->arr[ms->tkns->curr_tkn].type;
		ft_printf_fd(2, "minishell: syntax error near unexpected token `%s'\n",
			tkns_arr[tkn_type]);
		ms->exit_code = 2;
	}
	ft_free_tkns(ms);
	ft_free_ast(ast);
	ms->prsr_err = 0;
}
