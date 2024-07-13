/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glbr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 09:50:18 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/13 13:06:35 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int	ft_has_wldcrd(char *ptrn)
{
	size_t	i;

	i = 0;
	while (ptrn[i])
	{
		if (ptrn[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

int	ft_visib(char *p, char *s)
{
	if ((p[0] == 46 && s[0] == 46) || (p[0] != 46 && s[0] != 46))
		return (1);
	return (0);
}

void	ft_glbr_add_matches(t_glbr *glbr, char *s)
{
	DIR				*dir;
	struct dirent	*fl;
	int				count;

	count = 0;
	dir = opendir(".");
	fl = readdir(dir);
	while (fl && glbr->arr)
	{
		if (ft_wldcrd(fl->d_name, s) && ft_visib(fl->d_name, s))
		{
			ft_glbr_add(glbr, fl->d_name);
			count++;
		}
		fl = readdir(dir);
	}
	closedir(dir);
	if (!count)
		ft_glbr_add(glbr, s);
}

char	**ft_glbr(char **expd)
{
	t_glbr			glbr;
	size_t			i;

	if (!expd)
		return (NULL);
	i = 0;
	ft_init_glbr(&glbr);
	while (expd[i] && glbr.arr)
	{
		if (!ft_has_wldcrd(expd[i]))
			ft_glbr_add(&glbr, expd[i]);
		else
			ft_glbr_add_matches(&glbr, expd[i]);
		i++;
	}
	ft_free_split_null(expd);
	return (glbr.arr);
}
