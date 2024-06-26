/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_get_in_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:17:44 by jdach             #+#    #+#             */
/*   Updated: 2024/05/26 22:39:08 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_get_in(t_node *prev_node, t_cmd *cmd)
{
	int	fd;

	if (prev_node->action == PIPE)
	{
		fd = cmd->pipe[0];
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	exe_get_out(t_node *next_node, t_cmd *cmd)
{
	int	fd;

	if (next_node->action == PIPE)
	{
		pipe(cmd->pipe);
		fd = cmd->pipe[1];
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}


void	exe_get_in_out(t_list *cmd_list_item, t_cmd *cmd)
{
	if (cmd_list_item->prev)
		exe_get_in(cmd_list_item->prev->content, cmd);
	if (cmd_list_item->next)
		exe_get_out(cmd_list_item->next->content, cmd);
}
