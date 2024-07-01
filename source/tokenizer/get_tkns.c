/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tkns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:15:59 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/01 15:48:38 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_init_tkns(t_ms *ms)
{
	ms->tkns->size = 5;
	ms->tkns->to_add = 5;
	ms->tkns->i = 0;
	ms->tkns->curr_tkn = 0;
	ms->tkns->arr = (t_tkn *) malloc(ms->tkns->size * sizeof(t_tkn));
	if (!ms->tkns->arr)
		ft_free_tkns(ms);
}

void	ft_get_cmnd_str(t_ms *ms, char **line)
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
				return (ft_free_tkns(ms));
			}
		}
		tmp += 1;
	}
	cmnd_str = ft_substr(*line, 0, tmp - *line);
	if (!cmnd_str)
		return (ft_free_tkns(ms));
	ms->tkns->arr[ms->tkns->i].str = cmnd_str;
	*line = tmp;
}

void	ft_add_tkn(t_ms *ms, char **line)
{
	ft_tkns_realloc(ms);
	if (!ms->tkns)
		return ;
	ms->tkns->arr[ms->tkns->i].type = ft_is_operator(*line);
	if (ms->tkns->arr[ms->tkns->i].type == 0)
		ft_get_cmnd_str(ms, line); //UPDATE
	else
	{
		if (ms->tkns->arr[ms->tkns->i].type < 5)
			*line += 1;
		else
			*line += 2;
		ms->tkns->arr[ms->tkns->i].str = 0;
	}
	if (ms->tkns)
		ms->tkns->i++;
}

void	ft_get_tokens(t_ms *ms, char *line)
{
	//t_tkns	*tkns;

	if (!line || !line[0])
		return ;//(0);
	ms->tkns = ft_calloc(1, sizeof(t_tkns));
	if (!ms->tkns)
		return ;//(0);
	ft_init_tkns(ms);
	if (!ms->tkns)
		return ;//(0);
	while (ms->tkns && *line)
	{
		ft_skip_whitespace(&line);
		ft_add_tkn(ms, &line);
	}
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
