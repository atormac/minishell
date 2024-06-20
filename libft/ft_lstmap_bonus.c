/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:14:28 by atorma            #+#    #+#             */
/*   Updated: 2024/05/24 20:56:59 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list_new;
	t_list	*new;
	void	*applied;

	if (!lst || !f || !del)
		return (NULL);
	list_new = NULL;
	while (lst != NULL)
	{
		applied = f(lst->content);
		new = ft_lstnew(applied);
		if (!new)
		{
			del(applied);
			ft_lstclear(&list_new, (*del));
			return (NULL);
		}
		ft_lstadd_back(&list_new, new);
		lst = lst->next;
	}
	return (list_new);
}
