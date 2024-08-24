/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_directs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:17:44 by jdach             #+#    #+#             */
/*   Updated: 2024/08/23 16:52:11 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_directs(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	while (cmd_list_item && cmd_list_item->type != T_PIPE)
	{
		if (cmd_list_item->type == HEREDOC)
			exe_directs_here_doc(cmd_list_item);
		else if (cmd_list_item->type == REDIR_IN)
			exe_directs_redir_in(cmd_list_item);
		else if (cmd_list_item->type == REDIR_OUT)
			exe_directs_redir_out(cmd_list_item, cmd_data);
		else if (cmd_list_item->type == REDIR_APPEND)
			exe_directs_append(cmd_list_item, cmd_data);
		cmd_list_item = cmd_list_item->next;
	}
}
