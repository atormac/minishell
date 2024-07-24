/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd_tld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:17:55 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/24 14:05:54 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static inline char	*ft_expd_tilde(t_ms *ms)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = env_var_get(ms->env, "HOME");
	if (!tmp1)
		tmp2 = ft_strdup("");
	else
		tmp2 = ft_strdup(tmp1);
	return (tmp2);
}

void	ft_expd_tld(char **res, char *s, size_t *i, t_ms *ms)
{
	char	*tmp1;
	char	*tmp2;

	(*i)++;
	if (!s[*i] || s[*i] == ' ')
		tmp1 = ft_expd_tilde(ms);
	else
		tmp1 = ft_strdup("~");
	if (!tmp1)
		return (ft_free_null(res));
	tmp2 = ft_strjoin(*res, tmp1);
	free(*res);
	free(tmp1);
	*res = tmp2;
}
