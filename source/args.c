/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:39:08 by atorma            #+#    #+#             */
/*   Updated: 2024/06/26 18:43:41 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Remove this later
char	**get_args(char **cmd)
{
	char	*sp;

	sp = ft_strchr(*cmd, ' ');
	if (!sp || *(sp + 1) == '\0')
		return NULL;
	*sp = '\0';
	return ft_split(sp + 1, ' ');
}

size_t	args_count(char **args)
{
	size_t	ret;

	ret = 0;
	if (!args)
		return (ret);
	while (args[ret])
		ret++;
	return (ret);
}
