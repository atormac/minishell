/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:15:59 by lopoka            #+#    #+#             */
/*   Updated: 2024/06/26 11:42:15 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tokenizer.h"

int ft_is_quote(char *c)
{
	if (*c == '\'' || *c == '"')
		return (1);
	return (0);
}

char	*ft_quote_end(char *line)
{
	return (ft_strchr(line + 1, *line));
}

int	ft_is_whitespace(char *c)
{
	if (*c == ' ' || (*c >= '\t' && *c <= '\r'))
		return (1);
	return (0);
}

char	*ft_skip_whitespace(char **str)
{
	char	*tmp;
	
	tmp = *str;
	while (*tmp && ft_is_whitespace(tmp))
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

void	ft_init_tkns(t_tkns *tkns)
{
	tkns->size = 5;
	tkns->to_add = 5;
	tkns->i = 0;
	tkns->err = 0;
	tkns->arr = (t_tkn *) malloc(tkns->size * sizeof(t_tkn));
	if (!tkns->arr)
		tkns->err = 1;
}

void	ft_add_operator(char **line, t_tkns *tkns)
{
	int	type;

	ft_tkns_realloc(tkns);
	type = ft_is_operator(*line);
	if (type < 5)
		*line += 1;
	else
		*line += 2;
	tkns->arr[tkns->i].str = 0;
	tkns->arr[tkns->i].type = type;
	tkns->i++;
}

void	ft_add_cmnd(char **line, t_tkns *tkns)
{
	char	*tmp;

	tmp = *line;
	while (*tmp && !ft_is_operator(tmp) && !ft_is_whitespace(tmp))
	{
		if (ft_is_quote(tmp))
		{
			tmp = ft_quote_end(tmp);
			if (!tmp)
			{
				printf("No quote end\n");
				ft_free_tkns(tkns);
				tkns->err = 1;
				return ;
			}
			tmp += 1;
			break ;
		}
		else
			tmp += 1;
	}
	ft_tkns_realloc(tkns);
	tkns->arr[tkns->i].str = ft_substr(*line, 0, tmp - *line);
	tkns->arr[tkns->i].type = 0;
	tkns->i++;
	*line = tmp;
}

t_tkns	ft_line_to_tokens(char *line)
{
	t_tkns	tkns;

	ft_init_tkns(&tkns);
	if (tkns.err)
		return (tkns);
	while (*line && !tkns.err)
	{
		ft_skip_whitespace(&line);
		if (ft_is_operator(line))
			ft_add_operator(&line, &tkns);
		else
			ft_add_cmnd(&line, &tkns);
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

	char *line = "()<><<>> 'str1 str1'\"str2 str2\"&&||(((((Monika Konstanty)))))))<><><>||||||&&&&&&";
	printf("%s\n", line);
	t_tkns tkns = ft_line_to_tokens(line);
	for (int i = 0; i < tkns.i && !tkns.err; i++)
	{
		printf("Type %d str %s\n", tkns.arr[i].type, tkns.arr[i].str);
	}
	if (!tkns.err)
		ft_free_tkns(&tkns);
	return 0;
}
