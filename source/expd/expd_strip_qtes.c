/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd_strip_qtes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:59:48 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/10 14:35:52 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_strip_qtes(char *s)
{
	size_t	r;
	size_t	w;

	r = 0;
	w = 0;
	while (s[r])
	{
		if (s[r] == '"' || s[r] == '\'')
			r++;
		else
			s[w++] = s[r++];
	}
	s[w] = 0;
}
