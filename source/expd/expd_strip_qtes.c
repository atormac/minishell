/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd_strip_qtes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:59:48 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/16 21:55:47 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_strip_qtes(char *s)
{
	size_t	r;
	size_t	w;
	int		qte;

	r = 0;
	w = 0;
	while (s[r])
	{
		if (s[r] == '"' || s[r] == '\'')
		{
			qte = s[r++];
			while (s[r] && s[r] != qte)
				s[w++] = s[r++];
			if (s[r] == qte)
				r++;
		}
		else
			s[w++] = s[r++];
	}
	s[w] = 0;
}
