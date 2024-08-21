/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_set_in_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:55:09 by jdach             #+#    #+#             */
/*   Updated: 2024/08/21 20:54:00 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Runs through the commands until it finds a pipe. If there is a redirect
* stdin and stdout are mapped accordingly. When pipe is found a pipe is stored
* in cmd_data and we set the necessity that we need to write to and read from
* a pipe in pipe_status[0] and [1].
*/

void	exe_set_in_out(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	t_token_subtype	t;

	while (cmd_list_item && cmd_data->pipe_status[1] == -1)
	{
		t = cmd_list_item->type;
		if (t == HEREDOC || t == REDIR_IN || t == REDIR_OUT \
		|| t == REDIR_APPEND)
			exe_directs(cmd_list_item, cmd_data);
		else if (t == T_PIPE)
		{
			cmd_data->pipe_status[1] = 1;
			pipe(cmd_data->pipe);
			cmd_data->pipe_scenario = 1;
		}
		cmd_list_item = cmd_list_item->next;
	}
}
