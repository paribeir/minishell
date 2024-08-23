/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_set_in_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:55:09 by jdach             #+#    #+#             */
/*   Updated: 2024/08/23 16:25:10 by jdach            ###   ########.fr       */
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
	t_token_subtype	t;

	while (cmd_list_item && cmd_data->subshell_flag== -1)
	{
		t = cmd_list_item->type;
		if (t == HEREDOC || t == REDIR_IN || t == REDIR_OUT || t == REDIR_APPEND)
			exe_directs(cmd_list_item, cmd_data);
		else if (t == T_PIPE)
		{
			cmd_data->wr_to_pipe = 1;
			pipe(cmd_data->pipe);
			cmd_data->pipe_scenario = 1;
			cmd_data->subshell_flag = 1;
		}
		cmd_list_item = cmd_list_item->next;
	}
	cmd_data->subshell_flag = 1;
}
