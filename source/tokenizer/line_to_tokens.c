/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:15:59 by lopoka            #+#    #+#             */
/*   Updated: 2024/06/25 16:49:05 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tokenizer.h"


char	*ft_skip_whitespace(char **str)
{
	char	*tmp;
	
	tmp = *str;
	while (*tmp && (*tmp == ' ' || (*tmp >= '\t' && *tmp <= '\r')))
		tmp++;
	*str = tmp;
}

int	ft_is_operator(char *str)
{
	int		i;
	char	*operators;

	i = 0;
	operators = "()<>&|";
	while (operators[i])
	{
		if (i < 2 && *str == operators[i])
			return (i + 1);
		else if (i >= 2 && *str == operators[i])
		{
			if (*(str + 1) == operators[i])
				return (i + 3);
			else if (i < 4) 
				return (i + 1);
		}
		i++;
	}
	return (0);
}

void	ft_tkn_arr_realloc(t_tkn_arr *tkn_arr)
{
	if (tkn_arr->index >= tkn_arr->size)
	{
		tkn_arr->arr = ft_realloc_arr(tkn_arr->arr, tkn_arr->size, tkn_arr->toadd);
		if (!tkn_arr->arr)
			tkn_arr->err = 1;
		tkn_arr->size += tkn_arr->to_add;
	}
}

void	ft_init_tkn_arr(t_tkn_arr *tkn_arr)
{
	tkn_arr->size = 5;
	tkn_arr->to_add = 5;
	tkn_arr->i = 5;
	tkn_arr->err = 0;
	tkn_arr->arr = (t_tkn *) malloc(tkn_arr->size * sizeof(t_tkn);
	if (!tkn_arr->arr)
		tkn_arr->err = 1;
}

void	ft_add_operator(char *line, t_tkn_arr *tkn_arr)
{
	ft_tkn_arr_realloc(tkn_arr);
	ft_operator_add(line, tkn_arr);
}
t_tkn_arr	*ft_line_to_tokens(char *line)
{
	t_tkn_arr	tkn_arr;

	ft_init_tkn_arr(&tkn_arr);
	if (!tkn_arr.err)
		return (0),
	while (*line)
	{
		ft_skip_whitespace(&line);
		if (ft_is_operator(line))
			ft_add_operator(line, &tkn_llst);
		else
			ft_add_cmnd(line, &tkn_llst);
	}
	return (tkn_llst);
}
	
#include <stdio.h>

int main(void)		
{	

	printf("Is op %s %d\n", "(", ft_is_operator("("));
	printf("Is op %s %d\n", ")", ft_is_operator(")"));
	printf("Is op %s %d\n", "<", ft_is_operator("<"));
	printf("Is op %s %d\n", ">", ft_is_operator(">"));
	printf("Is op %s %d\n", "<<", ft_is_operator("<<"));
	printf("Is op %s %d\n", ">>", ft_is_operator(">>"));
	printf("Is op %s %d\n", "&&", ft_is_operator("&&"));
	printf("Is op %s %d\n", "||", ft_is_operator("||"));

	t_tkn_type aa;

	aa = 3;
	printf("0 is cmnd %d\n", aa == t_cmnd);
	return 0;
}
