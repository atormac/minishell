/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:15:59 by lopoka            #+#    #+#             */
/*   Updated: 2024/06/25 20:04:35 by lopoka           ###   ########.fr       */
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

void	ft_init_tkns(t_tkn_arr *tkns)
{
	tkns->size = 5;
	tkns->to_add = 5;
	tkns->i = 0;
	tkns->err = 0;
	tkns->arr = (t_tkn *) malloc(tkns->size * sizeof(t_tkn));
	if (!tkns->arr)
		tkns->err = 1;
}

void	ft_add_operator(char **line, t_tkn_arr *tkn_arr)
{
	int	type;

	ft_tkns_realloc(tkn_arr);
	type = ft_is_operator(*line);
	if (type < 5)
		*line += 1;
	else
		*line += 2;
	tkn_arr->arr[tkn_arr->i].str = 0;
	tkn_arr->arr[tkn_arr->i].type = type;
	tkn_arr->i++;
}
t_tkn_arr	ft_line_to_tokens(char *line)
{
	t_tkn_arr	tkns;

	ft_init_tkns(&tkns);
	if (tkns.err)
		return (tkns);
	while (*line && !tkns.err)
	{
		ft_skip_whitespace(&line);
		if (ft_is_operator(line))
			ft_add_operator(&line, &tkns);
		//else
		//	ft_add_cmnd(line, &tkn_llst);
	}
	return (tkns);
}
	
#include <stdio.h>

int main(void)		
{	
	/*
	printf("Is op %s %d\n", "(", ft_is_operator("("));
	printf("Is op %s %d\n", ")", ft_is_operator(")"));
	printf("Is op %s %d\n", "<", ft_is_operator("<"));
	printf("Is op %s %d\n", ">", ft_is_operator(">"));
	printf("Is op %s %d\n", "<<", ft_is_operator("<<"));
	printf("Is op %s %d\n", ">>", ft_is_operator(">>"));
	printf("Is op %s %d\n", "&&", ft_is_operator("&&"));
	printf("Is op %s %d\n", "||", ft_is_operator("||"));
	*/
	char *line = "()<><<>>&&||((((()))))))<><><>||||||&&&&&&";
	printf("%s\n", line);
	t_tkn_arr tkn_arr = ft_line_to_tokens(line);
	for (int i = 0; i < tkn_arr.i; i++)
		printf("Type %d\n", tkn_arr.arr[i].type);
	ft_free_tkns(&tkn_arr);
	return 0;
}
