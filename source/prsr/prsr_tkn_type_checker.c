/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsr_tkn_type_checker.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:48:37 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/05 13:35:37 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int	ft_is_tkn(t_tkns *tkns)
{
	if (tkns->curr_tkn >= tkns->i)
		return (0);
	return (1);
}

int	ft_is_tkn_bop(t_tkns *tkns)
{
	int	type;

	if (!ft_is_tkn(tkns))
		return (0);
	type = tkns->arr[tkns->curr_tkn].type;
	if (type == t_pipe || type == t_or || type == t_and)
		return (type);
	return (0);
}

int	ft_is_tkn_io(t_tkns *tkns)
{
	int	type;

	if (!ft_is_tkn(tkns))
		return (0);
	type = tkns->arr[tkns->curr_tkn].type;
	if (type == t_lwr || type == t_bgr || type == t_lwrlwr || type == t_bgrbgr)
		return (type);
	return (0);
}

int	ft_is_tkn_cmnd(t_tkns *tkns)
{
	int	type;

	if (!ft_is_tkn(tkns))
		return (0);
	type = tkns->arr[tkns->curr_tkn].type;
	if (type == 0)
		return (1);
	return (0);
}
