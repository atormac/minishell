/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:12:16 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/06 13:12:25 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_free_null(char **s)
{
	free(*s);
	*s = NULL;
}

void	expd_prep(t_ms *ms, t_ast *ast)
{
	size_t	i;
	char	*s;
	char	*res;

	s = ast->str;
	if (!s)
		return ;
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
	free(ast->str);
	ast->str = res;
	ft_rm_empty_substrs(ast->str);
	ast->expd_str = ft_expd_split_sub(ast->str, ' ', 1);
}

void	ft_expd_ast(t_ms *ms, t_ast *ast)
{
	t_ast	*curr;

	if (!ast)
		return ;
	if (ast->type == 0)
	{
		expd_prep(ms, ast);
		curr = ast->io;
		while (curr)
		{
			expd_prep(ms, curr);
			curr = curr->io;
		}
	}
	if (ast->left)
		ft_expd_ast(ms, ast->left);
	if (ast->right)
		ft_expd_ast(ms, ast->right);
}
