/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:21:36 by jdach             #+#    #+#             */
/*   Updated: 2023/11/22 15:40:37 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list_item;
	t_list	*lst2;

	lst2 = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		new_list_item = ft_lstnew(f(lst->content));
		if (!new_list_item)
		{
			ft_lstdelone(new_list_item, del);
			return (NULL);
		}
		if (lst2 == NULL)
			lst2 = new_list_item;
		else
			ft_lstadd_back(&lst2, new_list_item);
		lst = lst->next;
	}
	return (lst2);
}
