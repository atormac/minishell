/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:39:08 by atorma            #+#    #+#             */
/*   Updated: 2024/07/10 13:27:35 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
