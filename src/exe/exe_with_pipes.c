/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_with_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 08:13:34 by jdach             #+#    #+#             */
/*   Updated: 2024/09/12 16:50:49 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_with_pipes_store_pid(int pid, t_cmd *cmd_data)
{
	t_list			*exit_status_list_item;
	t_exit_status	*exit_status;

	exit_status = malloc(sizeof(t_exit_status));
	exit_status->exit_status = 99999;
	exit_status->pid = pid;
	exit_status_list_item = ft_lstnew(exit_status);
	ft_lstadd_back(&cmd_data->exit_codes, exit_status_list_item);
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
		else if (t == BLTIN_ECHO || t == BLTIN_CD || t == BLTIN_PWD || \
		t == BLTIN_EXPORT || t == BLTIN_UNSET || t == BLTIN_ENV || \
		t == BLTIN_EXIT)
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
		exe_cleanup(cmd_list_item, cmd_data);
		exit(EXIT_SUCCESS);
	}
	exe_with_pipes_store_pid(pid, cmd_data);
	exe_pipe_closing_parent(cmd_data);
}

void	exe_with_pipes(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	while (cmd_list_item && cmd_data->stop_exe == -1)
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
