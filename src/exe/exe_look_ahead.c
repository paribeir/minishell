/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_look_ahead.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:48:29 by jdach             #+#    #+#             */
/*   Updated: 2024/07/16 22:35:49 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_look_ahead(t_cmd_list *cmd_list_item, t_cmd *cmd)
{
	int			fd;
	t_cmd_list	*next_node;

	fd = 1;
	next_node = cmd_list_item->next;
	if (next_node->type == REDIR_OUT)
		fd = open(next_node->arguments[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (next_node->type == PIPE)
	{
		pipe(cmd->pipe);
		fd = cmd->pipe[1];
	}
	else if (next_node->type == REDIR_APPEND)
		fd = open(next_node->arguments[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
