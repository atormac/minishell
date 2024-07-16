/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkns.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:15:59 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/16 00:39:59 by lucas            ###   ########.fr       */
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

void	ft_quote_err(char c)
{
	ft_printf("minishell: unexpected EOF while ");
	ft_printf("looking for matching `%c'\n", c);
}

void	ft_get_cmnd_str(t_ms *ms, char **line)
{
	char	*tmp_line;
	char	*q_end;
	char	*cmnd_str;

	tmp_line = *line;
	while (*tmp_line && !ft_is_opr(tmp_line) && !ft_is_whtspc(tmp_line))
	{
		if (ft_is_quote(tmp_line))
		{
			q_end = ft_quote_end(tmp_line);
			if (q_end)
				tmp_line = q_end;
			else
				return (ft_free_tkns(ms), ft_quote_err(tmp_line[0]));
		}
		tmp_line += 1;
	}
	cmnd_str = ft_substr(*line, 0, tmp_line - *line);
	if (!cmnd_str)
		return (ft_free_tkns(ms));
	ms->tkns->arr[ms->tkns->i].str = cmnd_str;
	*line = tmp_line;
}

void	ft_add_tkn(t_ms *ms, char **line)
{
	ft_tkns_realloc(ms);
	if (!ms->tkns)
		return ;
	ms->tkns->arr[ms->tkns->i].type = ft_is_opr(*line);
	if (ms->tkns->arr[ms->tkns->i].type == 0)
		ft_get_cmnd_str(ms, line);
	else
	{
		if (ms->tkns->arr[ms->tkns->i].type <= 5)
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
	if (!line || !line[0])
		return ;
	ms->tkns = ft_calloc(1, sizeof(t_tkns));
	if (!ms->tkns)
		return ;
	ft_init_tkns(ms);
	if (!ms->tkns)
		return ;
	while (ms->tkns && *line)
	{
		ft_skip_whtspc(&line);
		if (*line)
			ft_add_tkn(ms, &line);
	}
}
