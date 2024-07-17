/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_get_in_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:17:44 by jdach             #+#    #+#             */
/*   Updated: 2024/07/17 10:27:49 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_get_out(t_cmd_list *cmd_list_item, t_cmd *cmd)
{
	if (cmd_list_item->next && cmd_list_item->next->type == T_PIPE)
	{
		pipe(cmd->pipe);
		dup2(cmd->pipe[1], STDOUT_FILENO);
		close(cmd->pipe[1]);
	}
	else
		dup2(cmd->saved_stdout, STDOUT_FILENO);
}

void	exe_get_in(t_cmd_list *cmd_list_item, t_cmd *cmd)
{
	if (cmd_list_item->prev && cmd_list_item->prev->type == T_PIPE)
	{
		dup2(cmd->pipe[0], STDIN_FILENO);
		close(cmd->pipe[0]);
	}
	else
		dup2(cmd->saved_stdin, STDIN_FILENO);
}

void	exe_get_in_out(t_cmd_list *cmd_list_item, t_cmd *cmd)
{
	exe_get_out(cmd_list_item, cmd);
	exe_get_in(cmd_list_item, cmd);
}
