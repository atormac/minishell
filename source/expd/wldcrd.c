/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wldcrd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:53:19 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/07 11:33:18 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_ptrn_qtes(char **ptrn, char *qte)
{
	if (**ptrn != '"' && **ptrn != '\'')
		return ;
	if (!*qte)
		*qte = **ptrn;
	else if (*qte == **ptrn)
		*qte = 0;
	(*ptrn)++;
}

int	ft_ptrn_strs(char *s, char **ptrn, char **wldcrd, char **common)
{
	while (**ptrn == '*')
		(*ptrn)++;
	if (!**ptrn)
		return (1);
	*wldcrd = *ptrn;
	*common = s;
	return (0);
}

int	ft_ptrn_match(char **s, char **ptrn, char **wldcrd, char **common)
{
	if (**ptrn == **s)
	{
		(*ptrn)++;
		(*s)++;
	}
	else if (*wldcrd)
	{
		*s = ++(*common);
		*ptrn = *wldcrd;
	}
	else
		return (0);
	return (1);
}

int	ft_wldcrd(char *s, char *ptrn)
{
	char	qte;
	char	*wldcrd;
	char	*common;

	qte = 0;
	wldcrd = 0;
	common = 0;
	while (*s)
	{
		ft_ptrn_qtes(&ptrn, &qte);
		if (*ptrn == '*' && !qte && ft_ptrn_strs(s, &ptrn, &wldcrd, &common))
			return (1);
		else if (!ft_ptrn_match(&s, &ptrn, &wldcrd, &common))
			return (0);
		ft_ptrn_qtes(&ptrn, &qte);
	}
	while (*ptrn == '*')
		ptrn++;
	ft_ptrn_qtes(&ptrn, &qte);
	return (!*ptrn);
}
/*
int	main(int ac, char **av)
{
	printf("res = %d\n", ft_wldcrd(av[2], av[1]));
	return (0);
}*/
