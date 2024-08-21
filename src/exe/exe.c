/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:46:53 by jdach             #+#    #+#             */
/*   Updated: 2024/08/21 22:05:22 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Setting the defautl values for command execution and checking if it is a pipe
 * situation. pipe_status[0] is for if we need to read from a pipe.
 * pipe_status[1] is for if we need to write to a pipe. We also need to set the
 * read end of the pipe to -1 as we will always copy that value to the
 * cmd_data->tmp_read_pipe_fd.
 */

void	exe_init_cmd_data(t_cmd *cmd_data, t_cmd_list *cmd_list_item)
{
	cmd_data->saved_stdin = dup(STDIN_FILENO);
	cmd_data->saved_stdout = dup(STDOUT_FILENO);
	cmd_data->pipe[0] = -1;
	cmd_data->pipe_status[0] = -1;
	cmd_data->pipe_status[1] = -1;
	cmd_data->exit_status = 0;
	cmd_data->pipe_scenario = -1;
	cmd_data->sub_cmd_flag = -1;
	(void) cmd_list_item;
}

void	exe_reset_in_out(t_cmd *cmd_data)
{
	dup2(cmd_data->saved_stdin, STDIN_FILENO);
	close(cmd_data->saved_stdin);
	dup2(cmd_data->saved_stdout, STDOUT_FILENO);
	close(cmd_data->saved_stdout);
}

/*
* First calls exe_set_in_out to look for redirects up until a pipe or the end
* of the command. Calls binary and builtin execution afterwards. Finding a pipe
* will reset pipe status to -1 so that the next run of exe_set_in_out will look
* for redirects again.
*/

void	exe_map(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	t_token_subtype	t;

	t = cmd_list_item->type;
	exe_set_in_out(cmd_list_item, cmd_data);
	if (t == BINARY)
		exe_bin(cmd_list_item, cmd_data);
	else if (t == BLTIN_ECHO || t == BLTIN_CD || t == BLTIN_PWD || \
	t == BLTIN_EXPORT || t == BLTIN_UNSET || t == BLTIN_ENV || t == BLTIN_EXIT)
		exe_bltns(cmd_list_item, cmd_data);
	else if (t == T_PIPE)
	{
		cmd_data->sub_cmd_flag = -1;
		cmd_data->pipe_status[1] = -1;
		cmd_data->pipe_status[0] = 1;
	}
}

void	exe(t_cmd_list	*cmd_list_item, t_cmd *cmd_data)
{
	int		status;
	pid_t	pid;

	exe_init_cmd_data(cmd_data, cmd_list_item);
	while (cmd_list_item)
	{
		exe_map(cmd_list_item, cmd_data);
		cmd_list_item = cmd_list_item->next;
	}
	pid = wait(&status);
	while (pid > 0)
	{
		if (WIFEXITED(status))
			cmd_data->exit_status = WEXITSTATUS(status);
		pid = wait(&status);
	}
	exe_reset_in_out(cmd_data);
}
