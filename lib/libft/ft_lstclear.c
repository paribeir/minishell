/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 22:22:58 by joda              #+#    #+#             */
/*   Updated: 2024/09/03 19:25:15 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp_head;
	t_list	*temp_next;

	temp_head = *lst;
	while (temp_head != NULL)
	{
		temp_next = temp_head->next;
		del(temp_head->content);
		free(temp_head);
		temp_head = temp_next;
	}
	*lst = NULL;
}
