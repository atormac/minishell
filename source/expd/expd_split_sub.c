/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd_split_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:06:16 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/05 19:53:04 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static inline void	ft_rm_char(char *s, char c)
{
	int	rd;
	int	wr;

	rd = 0;
	wr = 0;
	while (s[rd])
	{
		if (s[rd] != c)
			s[wr++] = s[rd];
		rd++;
	}
	s[wr] = 0;
}

static inline char	**ft_free_split(char **arr, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(arr[j++]);
	free(arr);
	return (NULL);
}

static inline void	ft_find_substr(t_token *tk, const char **sp, int esc)
{
	char	*p;

	p = ft_strchr(*sp + 1, **sp);
	while (p && p[-1] == '\\' && esc)
		p = ft_strchr(p + 1, **sp);
	if (p)
	{
		tk->end = p + 1;
		*sp = p + 1;
	}
}

static inline t_token	ft_get_token(const char **sp, char sep, int esc)
{
	t_token		token;

	token.start = NULL;
	token.end = NULL;
	while (**sp && **sp == sep)
		(*sp)++;
	if (!**sp)
		return (token);
	token.start = *sp;
	while (**sp && **sp != sep)
	{
		if (**sp == '\\' && esc)
			(*sp)++;
		else if (**sp == '\'' || **sp == '"')
		{
			ft_find_substr(&token, sp, esc);
			if (token.end != NULL)
				return (token);
		}
		(*sp)++;
	}
	token.end = *sp;
	return (token);
}

static inline int	ft_count_wrds(const char *s, char sep, int esc)
{
	int		count;
	t_token	token;

	token = ft_get_token(&s, sep, esc);
	count = 0;
	while (token.start != NULL)
	{
		token = ft_get_token(&s, sep, esc);
		count++;
	}
	return (count);
}

static inline char	*ft_token_to_str(t_token token)
{
	size_t	len;
	char	*substr;

	len = token.end - token.start;
	substr = (char *) malloc(len + 1);
	if (!substr)
		return (NULL);
	ft_memcpy(substr, token.start, len);
	substr[len] = 0;
	return (substr);
}

char	**ft_expd_split_sub(const char *str, char sep, int esc)
{
	char	**res;
	int		words;
	t_token	token;
	int		i;

	words = ft_count_wrds(str, sep, esc);
	res = (char **) malloc((words + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	token = ft_get_token(&str, sep, esc);
	while (token.start != NULL)
	{
		res[i] = ft_token_to_str(token);
		if (!res[i])
			return (ft_free_split(res, i));
		if (esc)
			ft_rm_char(res[i], '\\');
		token = ft_get_token(&str, sep, esc);
		i++;
	}
	res[i] = NULL;
	return (res);
}