/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tkns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:15:59 by lopoka            #+#    #+#             */
/*   Updated: 2024/06/29 09:46:21 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tokenizer.h"

void	ft_init_tkns(t_tkns **tkns)
{
	(*tkns)->size = 5;
	(*tkns)->to_add = 5;
	(*tkns)->i = 0;
	(*tkns)->curr_tkn = 0;
	(*tkns)->arr = (t_tkn *) malloc((*tkns)->size * sizeof(t_tkn));
	if (!(*tkns)->arr)
		ft_free_tkns(tkns);
}

void	ft_get_cmnd_str(char **line, t_tkns **tkns)
{
	char	*tmp;
	char	*cmnd_str;

	tmp = *line;
	while (*tmp && !ft_is_operator(tmp) && !ft_is_whitespace(tmp))
	{
		if (ft_is_quote(tmp))
		{
			tmp = ft_quote_end(tmp);
			if (!tmp)
			{
				ft_printf("No quote end\n");
				return (ft_free_tkns(tkns));
			}
		}
		tmp += 1;
	}
	cmnd_str = ft_substr(*line, 0, tmp - *line);
	if (!cmnd_str)
		return (ft_free_tkns(tkns));
	(*tkns)->arr[(*tkns)->i].str = cmnd_str;
	*line = tmp;
}

void	ft_add_tkn(char **line, t_tkns **tkns)
{
	ft_tkns_realloc(tkns);
	if (!*tkns)
		return ;
	(*tkns)->arr[(*tkns)->i].type = ft_is_operator(*line);
	if ((*tkns)->arr[(*tkns)->i].type == 0)
		ft_get_cmnd_str(line, tkns);
	else
	{
		if ((*tkns)->arr[(*tkns)->i].type < 5)
			*line += 1;
		else
			*line += 2;
		(*tkns)->arr[(*tkns)->i].str = 0;
	}
	if (*tkns)
		(*tkns)->i++;
}

t_tkns	*ft_get_tokens(char *line)
{
	t_tkns	*tkns;

	if (!line || !line[0])
		return (0);
	tkns = ft_calloc(1, sizeof(t_tkns));
	if (!tkns)
		return (0);
	ft_init_tkns(&tkns);
	if (!tkns)
		return (0);
	while (tkns && *line)
	{
		ft_skip_whitespace(&line);
		ft_add_tkn(&line, &tkns);
	}
	return (tkns);
}
/*
int main(void)		
{		
	ft_printf("Is op %s %d\n", "(", ft_is_operator("("));
	ft_printf("Is op %s %d\n", ")", ft_is_operator(")"));
	ft_printf("Is op %s %d\n", "<", ft_is_operator("<"));
	ft_printf("Is op %s %d\n", ">", ft_is_operator(">"));
	ft_printf("Is op %s %d\n", "|", ft_is_operator("|"));
	ft_printf("Is op %s %d\n", "<<", ft_is_operator("<<"));
	ft_printf("Is op %s %d\n", ">>", ft_is_operator(">>"));
	ft_printf("Is op %s %d\n", "||", ft_is_operator("||"));
	ft_printf("Is op %s %d\n", "&&", ft_is_operator("&&"));
	ft_printf("Is op %s %d\n", "&", ft_is_operator("&"));

	char *line = "()<><<>> 's1 s1'\"s2 s2\"&&||(Monika Konstanty)<>||&&";
	//char *line = "'s1 s1'\"s2 s2\"&&|||ab&( abcd '12 34 56'cd (a && b)";
	//char *line = "";
	ft_printf("line %s\n", line);
	t_tkns *tkns = ft_get_tokens(line);

	if (tkns)
	{
		for (int i = 0; i < tkns->i; i++)
		{
			ft_printf("Type %d str %s\n", tkns->arr[i].type, tkns->arr[i].str);
		}
		ft_free_tkns(&tkns);
	}
	return 0;
}*/
