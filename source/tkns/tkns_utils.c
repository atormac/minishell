/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkns_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:31:46 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/02 13:23:16 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int	ft_is_quote(char *c)
{
	if (*c == '\'' || *c == '"')
		return (1);
	return (0);
}

char	*ft_quote_end(char *line)
{
	return (ft_strchr(line + 1, *line));
}

int	ft_is_whtspc(char *c)
{
	if (*c == ' ' || (*c >= '\t' && *c <= '\r'))
		return (1);
	return (0);
}

char	*ft_skip_whtspc(char **str)
{
	char	*tmp;

	tmp = *str;
	while (*tmp && ft_is_whtspc(tmp))
		tmp++;
	*str = tmp;
	return (NULL);
}

int	ft_is_opr(char *str)
{
	int		i;
	char	*operators;

	i = 0;
	operators = "()<>|&";
	while (operators[i])
	{
		if (i < 2 && *str == operators[i])
			return (i + 1);
		else if (i >= 2 && *str == operators[i])
		{
			if (*(str + 1) == operators[i])
				return (i + 4);
			else if (i < 5)
				return (i + 1);
		}
		i++;
	}
	return (0);
}
