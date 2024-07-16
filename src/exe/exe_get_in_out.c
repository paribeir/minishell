/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_get_in_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:17:44 by jdach             #+#    #+#             */
/*   Updated: 2024/07/16 22:38:43 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_get_in(t_cmd_list *prev_node, t_cmd *cmd)
{
	int	fd;

	if (prev_node->type == PIPE)
	{
		fd = cmd->pipe[0];
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	exe_get_out(t_cmd_list *next_node, t_cmd *cmd)
{
	int	fd;

	if (next_node->type == PIPE)
	{
		pipe(cmd->pipe);
		fd = cmd->pipe[1];
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}


void	exe_get_in_out(t_cmd_list *cmd_list_item, t_cmd *cmd)
{
	if (cmd_list_item->prev)
		exe_get_in(cmd_list_item->prev, cmd);
	if (cmd_list_item->next)
		exe_get_out(cmd_list_item->next, cmd);
}
