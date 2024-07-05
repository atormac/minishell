/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:39:08 by atorma            #+#    #+#             */
/*   Updated: 2024/07/05 18:20:06 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_args(char *str)
{
	char	**args;

	if (!str)
		return (NULL);
	args = ft_split(str, ' ');
	if (!args)
		error_print("malloc", NULL);
	return (args);
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
