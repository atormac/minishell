/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:12:16 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/03 17:46:17 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
#include "../../include/environment.h"

void	ft_expd_dlr(char **res, char *s, size_t *i, t_ms *ms);

void	ft_free_null(char **s)
{
	free(*s);
	*s = NULL;
}

void	ft_expd_rglr(char **res, char *s, size_t *i)
{
	char	*tmp1;
	char	*tmp2;
	size_t	bgn;

	bgn = *i;
	while (s[*i] && s[*i] != '\'' && s[*i] != '"' && s[*i] != '$')
		(*i)++;
	tmp1 = ft_substr(s, bgn, *i - bgn);
	if (!tmp1)
		return (ft_free_null(res));
	tmp2 = ft_strjoin(*res, tmp1);
	free(*res);
	free(tmp1);
	*res = tmp2;
}

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

int	ft_vld_var_chr(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

void	ft_expd_dlr(char **res, char *s, size_t *i, t_ms *ms)
{
	char	*tmp1;
	char	*tmp2;
	size_t	bgn;

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
	{
		bgn = *i;
		while (ft_vld_var_chr(s[*i]))
			(*i)++;
		tmp1 = ft_substr(s, bgn, *i - bgn);
		if (!tmp1)
			return (ft_free_null(res));
		tmp2 = env_var_get(ms->env, tmp1);
		free(tmp1);
		if (!tmp2)
			tmp1 = ft_strdup("");
		else
			tmp1 = ft_strdup(tmp2);
	}
	if (!tmp1)
		return (ft_free_null(res));
	tmp2 = ft_strjoin(*res, tmp1);
	free(*res);
	free(tmp1);
	*res = tmp2;
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
	//free(s);
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

/*
int main(void)
{
	char *s1 = " hello str 'aaa bbbb";
	char *s2 = expd_prep(s1);

	ft_printf("%s\n", s2);
	free(s2);
	return (0);
}*/
