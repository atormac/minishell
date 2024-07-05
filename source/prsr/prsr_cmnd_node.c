/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsr_cmnd_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:03:23 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/05 13:04:42 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

t_ast	*ft_get_cmnd(t_tkns *tkns, t_ms *ms)
{
	t_ast	*cmnd_node;

	if (ms->prsr_err)
		return (NULL);
	cmnd_node = ft_get_ast_node(0);
	if (!cmnd_node)
		return (ft_set_prsr_err(ms, e_mem), NULL); //MEM ERR HANDLE
	while (ft_is_tkn_cmnd(tkns) || ft_is_tkn_io(tkns))
	{
		if (ft_is_tkn_cmnd(tkns))
		{
			if (!ft_join_cmnd(tkns, cmnd_node))
				return (ft_free_ast(cmnd_node), ft_set_prsr_err(ms, e_mem), NULL); //MEM ERR HANDLE
		}
		else if (ft_is_tkn_io(tkns))
		{
			if (!ft_get_io(tkns, cmnd_node, ms))	
				return (ft_free_ast(cmnd_node), NULL); //ERR HANDLE IN FT_GET_IO
		} 
	}
	return (cmnd_node);
}

int	ft_join_cmnd(t_tkns *tkns, t_ast *cmnd_node)
{
	char	*tmp;

	if (!cmnd_node->str)
		cmnd_node->str = ft_strdup("");
	if (!cmnd_node->str)
		return (0);
	while (ft_is_tkn_cmnd(tkns))
	{	
		tmp = cmnd_node->str;
		cmnd_node->str = ft_strjoin_space(cmnd_node->str, tkns->arr[tkns->curr_tkn].str);
		free(tmp);
		if (!cmnd_node->str)
			return (0);
		tkns->curr_tkn++;
	}
	return (1);
}

char	*ft_strjoin_space(char *s1, char *s2)
{
	char	*part;
	char	*final;

	if (!s1 || !s2)
		return (0);
	if (!s1[0])
		part = ft_strjoin(s1, "");
	else
		part = ft_strjoin(s1, " ");
	if (!part)
		return (0);
	final = ft_strjoin(part, s2);
	free(part);
	return (final);
}
