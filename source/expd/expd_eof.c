/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd_eof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:26:43 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/24 17:27:05 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_expd_eof(t_ast *ast)
{
	int	pre;
	int	aft;

	pre = ft_strlen(ast->str);
	ft_strip_qtes(ast->str);
	aft = ft_strlen(ast->str);
	if (aft == pre)
		ast->do_hrdc_exp = 1;
}
