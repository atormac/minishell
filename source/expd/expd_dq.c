/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd_dq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:23:03 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/04 20:33:30 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_expd_dq_sub(char **res, char *s, size_t *i)
{
	char	*tmp1;
	char	*tmp2;
	size_t	bgn;

	bgn = *i;
	while (s[*i] && s[*i] != '"' && s[*i] != '$')
		(*i)++;
	if (!s[*i])
		return (ft_free_null(res));
	tmp1 = ft_substr(s, bgn, *i - bgn);
	if (!tmp1)
		return (ft_free_null(res));
	tmp2 = ft_strjoin(*res, tmp1);
	free(*res);
	free(tmp1);
	*res = tmp2;
}

void	ft_expd_dq(char **res, char *s, size_t *i, t_ms *ms)
{
	char	*tmp1;

	tmp1 = ft_strjoin(*res, "\"");
	if (!tmp1)
		return (ft_free_null(res));
	free(*res);
	*res = tmp1;
	(*i)++;
	while (s[*i] != '"' && res)
	{
		if (s[*i] == '$')
			ft_expd_dlr(res, s, i, ms);
		else
			ft_expd_dq_sub(res, s, i);
	}
	(*i)++;
	tmp1 = ft_strjoin(*res, "\"");
	if (!tmp1)
		return (ft_free_null(res));
	*res = tmp1;
}
