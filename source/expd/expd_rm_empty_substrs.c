/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd_rm_empty_substrs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:59:48 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/05 19:56:24 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_rm_empty_str(char *s)
{
	size_t	r;
	size_t	w;

	if (!s[2] && ((s[0] == 34 && s[1] == 34) || (s[0] == 39 && s[1] == 39)))
		return ;
	r = 0;
	w = 0;
	while (s[r])
	{
		if ((s[r] == 34 && s[r + 1] == 34) || (s[r] == 39 && s[r + 1] == 39))
			r += 2;
		else
			s[w++] = s[r++];
	}
	s[w] = 0;
}

/*
int main(int ac, char **av)
{
	(void) ac;
	char	*s = strdup(av[1]);
	
	ft_rm_empty_str(s);
	
	printf("After removal: %s\n", s);
	
	char	**s_arr = ft_expd_split_sub(s, ' ', 1);

	int i = 0;
	while (s_arr[i])
	{
		printf("%s\n", s_arr[i++]);
	}
	return (0);
}*/
