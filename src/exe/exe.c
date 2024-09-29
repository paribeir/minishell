/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:46:53 by jdach             #+#    #+#             */
/*   Updated: 2024/09/29 15:32:53 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Setting the defautl values for command execution and checking if it is a pipe
 * situation. rd_from_pipe is for if we need to read from a pipe.
 * wr_to_pipe is for if we need to write to a pipe. We also need to set the
 * read end of the pipe to -1 as we will always copy that value to the
 * cmd_data->tmp_read_pipe_fd.
 */

void	exe_setup(t_cmd *cmd_data, t_cmd_list *cmd_list_item)
{
	cmd_data->pipe[0] = -1;
	cmd_data->pipe[1] = -1;
	cmd_data->wr_to_pipe = -1;
	cmd_data->rd_from_pipe = -1;
	cmd_data->pipe_scenario = -1;
	cmd_data->stop_exe = -1;
	cmd_data->cmd_list_head = cmd_list_item;
	while (cmd_list_item && cmd_data->pipe_scenario == -1)
	{
		if (cmd_list_item->type == T_PIPE)
			cmd_data->pipe_scenario = 1;
		cmd_list_item = cmd_list_item->next;
	}
	cmd_data->subshell_running = -1;
}

void	exe_reset_in_out(t_cmd *cmd_data)
{
	dup2(cmd_data->saved_stdin, STDIN_FILENO);
	close(cmd_data->saved_stdin);
	dup2(cmd_data->saved_stdout, STDOUT_FILENO);
	close(cmd_data->saved_stdout);
}

void	exe(t_cmd_list	*cmd_list_item, t_cmd *cmd_data)
{
	exe_setup(cmd_data, cmd_list_item);
	if (cmd_data->pipe_scenario == 1)
		exe_with_pipes(cmd_list_item, cmd_data);
	else
		exe_without_pipes(cmd_list_item, cmd_data);
	exe_get_exit_status(cmd_data);
	exe_reset_in_out(cmd_data);
}
