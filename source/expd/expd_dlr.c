/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd_dlr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:17:55 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/04 20:56:52 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int	ft_vld_var_chr(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*ft_expd_var(char *s, size_t *i, t_ms *ms)
{
	char	*tmp1;
	char	*tmp2;
	size_t	bgn;

	bgn = *i;
	while (ft_vld_var_chr(s[*i]))
		(*i)++;
	tmp1 = ft_substr(s, bgn, *i - bgn);
	if (!tmp1)
		return (NULL);
	tmp2 = env_var_get(ms->env, tmp1);
	free(tmp1);
	if (!tmp2)
		tmp1 = ft_strdup("");
	else
		tmp1 = ft_strdup(tmp2);
	return (tmp1);
}

void	ft_expd_dlr(char **res, char *s, size_t *i, t_ms *ms)
{
	char	*tmp1;
	char	*tmp2;

	(*i)++;
	if (ft_isdigit(s[*i]) || s[*i] == '@')
	{
		(*i)++;
		tmp1 = ft_strdup("");
	}
	else if (s[*i] == '?')
	{
		(*i)++;
		tmp1 = ft_itoa(ms->exit_code);
	}
	else if (!ft_vld_var_chr(s[*i]))
		tmp1 = ft_strdup("$");
	else
		tmp1 = ft_expd_var(s, i, ms);
	if (!tmp1)
		return (ft_free_null(res));
	tmp2 = ft_strjoin(*res, tmp1);
	free(*res);
	free(tmp1);
	*res = tmp2;
}
