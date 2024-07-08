/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:15:56 by jdach             #+#    #+#             */
/*   Updated: 2024/06/24 17:28:10 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_init(t_cmd *cmd)
{
	t_list	*list_item;
	t_node	*node;
	char	*str;

	cmd->nodes = NULL;


	node = malloc(sizeof(t_node));
	node->action = REDIR_IN;
	node->params = ft_split("infile", ' ');
	list_item = ft_lstnew(node);
	ft_lstadd_back(&cmd->nodes, list_item);

	node = malloc(sizeof(t_node));
	node->action = BIN1;
	node->binary = "cat";
	node->params = NULL;
	node->flags = NULL;
	list_item = ft_lstnew(node);
	ft_lstadd_back(&cmd->nodes, list_item);

	node = malloc(sizeof(t_node));
	node->action = APPEND1;
	node->params = ft_split("outfile", ' ');
	list_item = ft_lstnew(node);
	ft_lstadd_back(&cmd->nodes, list_item);
}
