/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 01:10:21 by jdach             #+#    #+#             */
/*   Updated: 2024/08/22 17:56:00 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_bin(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	char	*path;
	char	**args;
	int		pid;
	int		execve_return;

	pid = fork();
	if (pid == 0)
	{
		path = exe_bin_get_bin_path(cmd_list_item, cmd_data);
		args = exe_bin_args(cmd_list_item->arguments, cmd_list_item->binary);
		if (cmd_data->rd_from_pipe == 1)
		{
			dup2(cmd_data->tmp_read_pipe_fd, STDIN_FILENO);
			close(cmd_data->tmp_read_pipe_fd);
		}
		if (cmd_data->wr_to_pipe == 1)
		{
			dup2(cmd_data->pipe[1], STDOUT_FILENO);
			close(cmd_data->pipe[1]);
			close(cmd_data->pipe[0]);
		}
		execve_return = execve(path, args, cmd_data->envp);
		free(path);
		free(args);
		if (execve_return == -1)
			exit (127);
	}
	if (cmd_data->wr_to_pipe == 1)
	{
		close(cmd_data->pipe[1]);
		if (cmd_data->rd_from_pipe == 1)
		{
			close(cmd_data->tmp_read_pipe_fd);
			cmd_data->rd_from_pipe = 0;
		}
		cmd_data->tmp_read_pipe_fd = cmd_data->pipe[0];
	}
	if (cmd_data->rd_from_pipe == 1)
		close(cmd_data->tmp_read_pipe_fd);
}
