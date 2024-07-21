/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_directs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:17:44 by jdach             #+#    #+#             */
/*   Updated: 2024/07/21 16:32:30 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_directs(t_cmd_list *cmd_list_item, t_cmd *cmd_env)
{
	if (cmd_list_item->type == T_PIPE)
		exe_directs_pipe_in(cmd_env);
	else if (cmd_list_item->type == HEREDOC)
		exe_directs_here_doc(cmd_list_item);
	else if (cmd_list_item->type == REDIR_IN)
		exe_directs_redir_in(cmd_list_item);
	else if (cmd_list_item->type == REDIR_OUT)
		exe_directs_redir_out(cmd_list_item);
	else if (cmd_list_item->type == REDIR_APPEND)
		exe_directs_append(cmd_list_item);
}
