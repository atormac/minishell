/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd_rm_empty_substrs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:59:48 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/24 11:34:56 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_rm_empty_substrs(char *s)
{
	size_t	r;
	size_t	w;
	int		qte;

	if (!s || !s[0] || !s[1])
		return ;
	if (!s[2] && ((s[0] == 34 && s[1] == 34) || (s[0] == 39 && s[1] == 39)))
		return ;
	r = 0;
	w = 0;
	while (s[r])
	{
		if ((s[r] == 34 && s[r + 1] == 34) || (s[r] == 39 && s[r + 1] == 39))
			r += 2;
		else if (s[r] == '"' || s[r] == '\'')
		{
			qte = s[r];
			s[w++] = s[r++];
			while (s[r] && s[r] != qte)
				s[w++] = s[r++];
		}
		else
			s[w++] = s[r++];
	}
	s[w] = 0;
}
