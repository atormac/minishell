/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:31:27 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/06 13:16:07 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_rm_char(char *s, char c)
{
	int	rd;
	int	wr;

	rd = 0;
	wr = 0;
	while (s[rd])
	{
		if (s[rd] != c)
			s[wr++] = s[rd];
		rd++;
	}
	s[wr] = 0;
}

char	**ft_free_split(char **arr, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(arr[j++]);
	free(arr);
	return (NULL);
}

void	ft_free_split_null(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
