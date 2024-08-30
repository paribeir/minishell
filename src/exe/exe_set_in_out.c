/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_set_in_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:55:09 by jdach             #+#    #+#             */
/*   Updated: 2024/08/30 08:11:09 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Runs through the commands until it finds a pipe. If there is a redirect
* stdin and stdout are mapped accordingly. When pipe is found a pipe is stored
* in cmd_data and we set the necessity that we need to write to
* a pipe with wr_to_pipe.
*/

void	exe_set_in_out(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	int	pipe_found;

	pipe_found = -1;
	while (cmd_list_item && pipe_found == -1 && cmd_data->stop_exe == -1)
	{
		if (cmd_list_item->type == HEREDOC)
			exe_directs_here_doc(cmd_list_item);
		else if (cmd_list_item->type == REDIR_IN)
			exe_directs_redir_in(cmd_list_item, cmd_data);
		else if (cmd_list_item->type == REDIR_OUT)
			exe_directs_redir_out(cmd_list_item, cmd_data);
		else if (cmd_list_item->type == REDIR_APPEND)
			exe_directs_append(cmd_list_item, cmd_data);
		if (cmd_list_item->type == T_PIPE)
			pipe_found = 1;
		cmd_list_item = cmd_list_item->next;
	}
}
