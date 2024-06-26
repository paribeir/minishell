/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:46:53 by jdach             #+#    #+#             */
/*   Updated: 2024/06/24 17:28:26 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_run(t_cmd *cmd)
{
	t_list	*cmd_list_item;

	cmd_list_item = cmd->nodes;
	while (cmd_list_item)
	{
		if (((t_node *)(cmd_list_item->content))->action == BIN1)
			exe_bin(cmd_list_item, cmd);
		else if (((t_node *)(cmd_list_item->content))->action == HEREDOC1)
			exe_here_doc(cmd_list_item, cmd);
		else if (((t_node *)(cmd_list_item->content))->action == REDIR_IN1)
			exe_redir_in(cmd_list_item, cmd);
		else if (((t_node *)(cmd_list_item->content))->action == BLTN_ECHO1)
			exe_bltn_echo(cmd_list_item, cmd);
		cmd_list_item = cmd_list_item->next;
	}
	while (wait(NULL) > 0)
		;
}
