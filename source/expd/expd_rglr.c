/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd_rglr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:20:53 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/28 11:09:14 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_expd_rglr(char **res, char *s, size_t *i)
{
	char	*tmp1;
	char	*tmp2;
	size_t	bgn;

	bgn = *i;
	while (s[*i] && s[*i] != '\'' && s[*i] != '"' && s[*i] != '$'
		&& s[*i] != '~')
		(*i)++;
	tmp1 = ft_substr(s, bgn, *i - bgn);
	if (!tmp1)
		return (ft_free_null(res));
	tmp2 = ft_strjoin(*res, tmp1);
	free(*res);
	free(tmp1);
	*res = tmp2;
}

void	ft_expd_rglr_hrdc(char **res, char *s, size_t *i)
{
	char	*tmp1;
	char	*tmp2;
	size_t	bgn;

	bgn = *i;
	while (s[*i] && s[*i] != '$')
		(*i)++;
	tmp1 = ft_substr(s, bgn, *i - bgn);
	if (!tmp1)
		return (ft_free_null(res));
	tmp2 = ft_strjoin(*res, tmp1);
	free(*res);
	free(tmp1);
	*res = tmp2;
}
