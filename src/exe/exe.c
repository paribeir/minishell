/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:46:53 by jdach             #+#    #+#             */
/*   Updated: 2024/08/17 20:53:23 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_init_cmd_data(t_cmd *cmd_data)
{
	cmd_data->saved_stdin = dup(STDIN_FILENO);
	cmd_data->saved_stdout = dup(STDOUT_FILENO);
	cmd_data->pipe[0] = -1;
	cmd_data->pipe[0] = -1;
	cmd_data->pipe_status = -1;
	cmd_data->fdout_status = -1;
	cmd_data->exit_status = 0;
}

void	exe_reset_in_out(t_cmd *cmd_data)
{
	dup2(cmd_data->saved_stdin, STDIN_FILENO);
	close(cmd_data->saved_stdin);
	dup2(cmd_data->saved_stdout, STDOUT_FILENO);
	close(cmd_data->saved_stdout);
}

void	exe_map(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	t_token_subtype	t;

	t = cmd_list_item->type;
	if (t == BINARY)
		exe_bin(cmd_list_item, cmd_data);
	else if (t == T_PIPE)
	{
		exe_pipe_in(cmd_data);
		cmd_data->pipe_status = -1;
		cmd_data->fdout_status = -1;
	}
	else if (t == BLTIN_ECHO || t == BLTIN_CD || t == BLTIN_PWD || \
	t == BLTIN_EXPORT || t == BLTIN_UNSET || t == BLTIN_ENV || t == BLTIN_EXIT)
		exe_bltns(cmd_list_item, cmd_data);
}

void	exe_set_in_out(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	t_token_subtype	t;

	while (cmd_list_item && cmd_data->pipe_status == -1)
	{
		t = cmd_list_item->type;
		if (t == HEREDOC || t == REDIR_IN || t == REDIR_OUT \
		|| t == REDIR_APPEND)
			exe_directs(cmd_list_item, cmd_data);
		else if (t == T_PIPE)
		{
			if (cmd_data->pipe_status == -1)
			{
				cmd_data->pipe_status = 1;
				exe_pipe_out(cmd_data);
			}
		}
		cmd_list_item = cmd_list_item->next;
	}
}

void	exe(t_cmd_list	*cmd_list_item, t_cmd *cmd_data)
{
	int		status;
	pid_t	pid;

	exe_init_cmd_data(cmd_data);
	while (cmd_list_item)
	{
		if (cmd_data->pipe_status == -1)
			exe_set_in_out(cmd_list_item, cmd_data);
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
