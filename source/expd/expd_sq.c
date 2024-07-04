/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd_sq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:21:47 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/04 20:33:41 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_expd_sq(char **res, char *s, size_t *i)
{
	char	*tmp1;
	char	*tmp2;
	size_t	bgn;

	bgn = *i;
	(*i)++;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	if (!s[*i])
		return (ft_free_null(res));
	(*i)++;
	tmp1 = ft_substr(s, bgn, *i - bgn);
	if (!tmp1)
		return (ft_free_null(res));
	tmp2 = ft_strjoin(*res, tmp1);
	free(*res);
	free(tmp1);
	*res = tmp2;
}
