/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_look_ahead.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:48:29 by jdach             #+#    #+#             */
/*   Updated: 2024/06/24 17:28:17 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_look_ahead(t_list *cmd_list_item, t_cmd *cmd)
{
	int		fd;
	t_node	*next_node;

	fd = 1;
	next_node = (t_node *)((cmd_list_item->next)->content);
	if (next_node->action == REDIR_OUT)
		fd = open(next_node->params[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (next_node->action == PIPE)
	{
		pipe(cmd->pipe);
		fd = cmd->pipe[1];
	}
	else if (next_node->action == APPEND1)
		fd = open(next_node->params[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
