/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:12:16 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/28 11:17:51 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_free_null(char **s)
{
	free(*s);
	*s = NULL;
}

void	ft_post_expd(t_ms *ms, t_ast *ast, char *part_expd_str)
{
	if (!part_expd_str)
	{
		ms->prsr_err = e_mem;
		return ;
	}
	ast->expd_str = ft_expd_split_sub(part_expd_str, ' ');
	free(part_expd_str);
	ast->expd_str = ft_glbr(ast->expd_str);
	if (!ast->expd_str)
		ms->prsr_err = e_mem;
}

void	ft_expd_str(t_ms *ms, t_ast *ast)
{
	size_t	i;
	char	*res;

	if (!ast->str)
		return ;
	if (ast->type == 6)
		return (ft_expd_eof(ast));
	res = ft_strdup("");
	i = 0;
	while (ast->str[i] && res)
	{
		if (ast->str[i] == '$')
			ft_expd_dlr(&res, ast->str, &i, ms);
		else if (ast->str[i] == '~')
			ft_expd_tld(&res, ast->str, &i, ms);
		else if (ast->str[i] == '\'')
			ft_expd_sq(&res, ast->str, &i);
		else if (ast->str[i] == '"')
			ft_expd_dq(&res, ast->str, &i, ms);
		else
			ft_expd_rglr(&res, ast->str, &i);
	}
	ft_post_expd(ms, ast, res);
}

char	*ft_expd_heredoc(char *s, t_ms *ms)
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
		else
			ft_expd_rglr_hrdc(&res, s, &i);
	}
	return (res);
}

void	ft_expd_ast(t_ms *ms, t_ast *ast)
{
	if (!ast || ms->prsr_err)
		return ;
	if (ast->type == 0)
		ast->pid = -2;
	ft_expd_str(ms, ast);
	ft_expd_ast(ms, ast->io);
	ft_expd_ast(ms, ast->left);
	ft_expd_ast(ms, ast->right);
}
