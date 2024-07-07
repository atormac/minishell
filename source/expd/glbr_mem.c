/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glbr_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:41:33 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/07 12:44:21 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_init_glbr(t_glbr *glbr)
{
	glbr->size = 5;
	glbr->to_add = 5;
	glbr->i = 0;
	glbr->curr = 0;
	glbr->arr = (char **) calloc(glbr->size, sizeof(char *));
}

void	ft_glbr_realloc(t_glbr *glbr)
{
	void	*dst;

	if (!glbr->arr || glbr->i < glbr->size - 1)
		return ;
	dst = (char **) calloc(glbr->size + glbr->to_add, sizeof(char *));
	if (!dst)
		return (ft_free_glbr(glbr));
	ft_memmove(dst, glbr->arr, glbr->size * sizeof(char *));
	free(glbr->arr);
	glbr->arr = dst;
	glbr->size += glbr->to_add;
}

void	ft_glbr_add(t_glbr *glbr, char *s)
{
	ft_glbr_realloc(glbr);
	if (!glbr->arr)
		return ;
	glbr->arr[glbr->i] = ft_strdup(s);
	if (!glbr->arr[glbr->i])
		ft_free_glbr(glbr);
	if (glbr->arr)
		glbr->i++;
}

void	ft_free_glbr(t_glbr *glbr)
{
	size_t	i;

	if (!glbr->arr)
		return ;
	i = 0;
	while (i < glbr->i)
		free(glbr->arr[i++]);
	free(glbr->arr);
	glbr->arr = 0;
}
