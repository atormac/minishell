/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:13:15 by atorma            #+#    #+#             */
/*   Updated: 2024/04/17 18:40:42 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*entry;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	entry = *lst;
	while (entry != NULL)
	{
		tmp = entry->next;
		ft_lstdelone(entry, del);
		entry = tmp;
	}
	*lst = NULL;
}
