/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:46:53 by jdach             #+#    #+#             */
/*   Updated: 2024/08/23 19:54:02 by jdach            ###   ########.fr       */
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

void	exe_init_cmd_data(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	cmd_data->saved_stdin = dup(STDIN_FILENO);
	cmd_data->saved_stdout = dup(STDOUT_FILENO);
	cmd_data->pipe[0] = -1;
	cmd_data->pipe[1] = -1;
	cmd_data->wr_to_pipe = -1;
	cmd_data->rd_from_pipe = -1;
	cmd_data->pipe_scenario = -1;
	while (cmd_list_item && cmd_data->pipe_scenario == -1)
	{
		if (cmd_list_item->type == T_PIPE)
			cmd_data->pipe_scenario = 1;
		cmd_list_item = cmd_list_item->next;
	}
	cmd_data->subshell_running = -1;
	cmd_data->exit_status = 0;
}

void	exe_reset_in_out(t_cmd *cmd_data)
{
	dup2(cmd_data->saved_stdin, STDIN_FILENO);
	close(cmd_data->saved_stdin);
	dup2(cmd_data->saved_stdout, STDOUT_FILENO);
	close(cmd_data->saved_stdout);
}

void	exe_with_pipes_is_pipe_ahead(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	while (cmd_list_item && cmd_data->wr_to_pipe == -1)
	{
		if (cmd_list_item->type == T_PIPE)
		{
			cmd_data->wr_to_pipe = 1;
			pipe(cmd_data->pipe);
		}
		cmd_list_item = cmd_list_item->next;
	}
}

void	exe_with_pipes_map(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	t_token_subtype	t;

	while (cmd_list_item && cmd_data->subshell_running == 1)
	{
		t = cmd_list_item->type;
		if (t == BINARY)
			exe_bin(cmd_list_item, cmd_data);
		else if (t == BLTIN_ECHO || t == BLTIN_CD || t == BLTIN_PWD || t == BLTIN_EXPORT || t == BLTIN_UNSET || t == BLTIN_ENV || t == BLTIN_EXIT)
			exe_bltns(cmd_list_item, cmd_data);
		else if (cmd_list_item->type == T_PIPE)
			cmd_data->subshell_running = -1;
		cmd_list_item = cmd_list_item->next;
	}
}

void	exe_with_pipes_start_pipe(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	int	pid;

	if (cmd_data->rd_from_pipe == 1)
		cmd_data->tmp_read_pipe_fd = cmd_data->pipe[0];
	exe_with_pipes_is_pipe_ahead(cmd_list_item, cmd_data);
	pid = fork();
	if (pid == 0)
	{
		if (cmd_data->rd_from_pipe == 1)
		{
			dup2(cmd_data->tmp_read_pipe_fd, STDIN_FILENO);
			close(cmd_data->tmp_read_pipe_fd);
		}
		exe_pipe_closing_child(cmd_data);
		exe_set_in_out(cmd_list_item, cmd_data);
		exe_with_pipes_map(cmd_list_item, cmd_data);
	}
	exe_pipe_closing_parent(cmd_data);
}

void	exe_with_pipes(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	while (cmd_list_item)
	{
		if (cmd_data->subshell_running == -1)
		{
			cmd_data->subshell_running = 1;
			exe_with_pipes_start_pipe(cmd_list_item, cmd_data);
		}
		if (cmd_list_item->type == T_PIPE)
		{
			cmd_data->subshell_running = -1;
			cmd_data->rd_from_pipe = 1;
			cmd_data->wr_to_pipe = -1;
		}
		cmd_list_item = cmd_list_item->next;
	}
}

void	exe_without_pipes(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	int				pid;
	t_token_subtype	t;

	exe_set_in_out(cmd_list_item, cmd_data);
	t = cmd_list_item->type;
	if (t == BINARY)
	{
		pid = fork();
		if (pid == 0)
			exe_bin(cmd_list_item, cmd_data);
	}
	else if (t == BLTIN_ECHO || t == BLTIN_CD || t == BLTIN_PWD || t == BLTIN_EXPORT || t == BLTIN_UNSET || t == BLTIN_ENV || t == BLTIN_EXIT)
		exe_bltns(cmd_list_item, cmd_data);
}

void	exe(t_cmd_list	*cmd_list_item, t_cmd *cmd_data)
{
	int		status;
	pid_t	pid;

	exe_init_cmd_data(cmd_list_item, cmd_data);
	if (cmd_data->pipe_scenario == 1)
		exe_with_pipes(cmd_list_item, cmd_data);
	else
		exe_without_pipes(cmd_list_item, cmd_data);
	pid = wait(&status);
	while (pid > 0)
	{
		if (WIFEXITED(status))
			cmd_data->exit_status = WEXITSTATUS(status);
		pid = wait(&status);
	}
	exe_reset_in_out(cmd_data);
}
