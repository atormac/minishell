/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tkns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:15:59 by lopoka            #+#    #+#             */
/*   Updated: 2024/06/26 18:28:46 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tokenizer.h"

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

void	ft_get_cmnd_str(char **line, t_tkns *tkns)
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
		}
		tmp += 1;
	}
	tkns->arr[tkns->i].str = ft_substr(*line, 0, tmp - *line);
	*line = tmp;
}

void	ft_add_tkn(char **line, t_tkns *tkns)
{
	ft_tkns_realloc(tkns);
	tkns->arr[tkns->i].type = ft_is_operator(*line);
	if (tkns->arr[tkns->i].type == 0)
		ft_get_cmnd_str(line, tkns);
	else
	{
		if (tkns->arr[tkns->i].type < 5)
			*line += 1;
		else
			*line += 2;
		tkns->arr[tkns->i].str = 0;
	}
	tkns->i++;
}

t_tkns	ft_get_tokens(char *line)
{
	t_tkns	tkns;

	ft_init_tkns(&tkns);
	if (tkns.err)
		return (tkns);
	while (*line && !tkns.err)
	{
		ft_skip_whitespace(&line);
		ft_add_tkn(&line, &tkns);
	}
	return (tkns);
}
/*
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

	//char *line = "()<><<>> 's1 s1'\"s2 s2\"&&||(Monika Konstanty)<>||&&";
	char *line = "'s1 s1'\"s2 s2\"&&|||ab&( abcd '12 34 56'cd (a && b)";
	printf("%s\n", line);
	t_tkns tkns = ft_get_tokens(line);
	for (int i = 0; i < tkns.i && !tkns.err; i++)
	{
		printf("Type %d str %s\n", tkns.arr[i].type, tkns.arr[i].str);
	}
	if (!tkns.err)
		ft_free_tkns(&tkns);
	return 0;
}*/
