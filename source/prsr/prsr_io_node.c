/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsr_io_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:59:38 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/05 13:34:22 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int	ft_get_io(t_tkns *tkns, t_ast *cmnd_node, t_ms *ms)
{
	t_ast	*io_node;
	int		type;

	if (ms->prsr_err)
		return (0);
	while (ft_is_tkn_io(tkns))
	{
		type = ft_is_tkn_io(tkns);
		tkns->curr_tkn++;
		if (!ft_is_tkn_cmnd(tkns))
			return (ft_set_prsr_err(ms, e_sntx), 0);
		io_node = ft_get_ast_node(type);
		if (!io_node)
			return (ft_set_prsr_err(ms, e_mem), 0);
		io_node->str = ft_strdup(tkns->arr[tkns->curr_tkn].str);
		if (!io_node->str)
			return (ft_set_prsr_err(ms, e_mem), free(io_node), 0);
		ft_add_io_node(cmnd_node, io_node);
		tkns->curr_tkn++;
	}
	return (1);
}

void	ft_add_io_node(t_ast *cmnd_node, t_ast *io_node)
{
	t_ast	*curr;

	if (!cmnd_node->io)
	{
		cmnd_node->io = io_node;
		return ;
	}
	curr = cmnd_node->io;
	while (curr && curr->io)
		curr = curr->io;
	curr->io = io_node;
}
