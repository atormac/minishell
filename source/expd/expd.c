/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:12:16 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/04 20:37:56 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_free_null(char **s)
{
	free(*s);
	*s = NULL;
}

char	*expd_prep(char *s, t_ms *ms)
{
	size_t	i;
	char	*res;

	if (!s)
		return (NULL);
	res = ft_strdup("");
	i = 0;
	while (s[i] && res)
	{
		if (s[i] == '$')
			ft_expd_dlr(&res, s, &i, ms);
		else if (s[i] == '\'')
			ft_expd_sq(&res, s, &i);
		else if (s[i] == '"')
			ft_expd_dq(&res, s, &i, ms);
		else
			ft_expd_rglr(&res, s, &i);
	}
	return (res);
}

void	ft_expd_ast(t_ms *ms, t_ast *ast)
{
	t_ast	*curr;
	char	*tmp;

	if (!ast)
		return ;
	if (ast->type == 0)
	{
		tmp = expd_prep(ast->str, ms);
		free(ast->str);
		ast->str = tmp;
		curr = ast->io;
		while (curr)
		{
			tmp = expd_prep(curr->str, ms);
			free(curr->str);
			curr->str = tmp;
			curr = curr->io;
		}
	}
	if (ast->left)
		ft_expd_ast(ms, ast->left);
	if (ast->right)
		ft_expd_ast(ms, ast->right);
}
