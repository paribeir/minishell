/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_set_in_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:55:09 by jdach             #+#    #+#             */
/*   Updated: 2024/08/23 18:48:52 by jdach            ###   ########.fr       */
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
	int				pipe_found;

	pipe_found = -1;
	while (cmd_list_item && pipe_found == -1)
	{
		t = cmd_list_item->type;
		if (t == HEREDOC || t == REDIR_IN || t == REDIR_OUT || t == REDIR_APPEND)
			exe_directs(cmd_list_item, cmd_data);
		if (t == T_PIPE)
			pipe_found = 1;
		cmd_list_item = cmd_list_item->next;
	}
}
