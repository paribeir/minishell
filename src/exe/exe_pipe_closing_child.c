/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe_closing_child.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:25:03 by jdach             #+#    #+#             */
/*   Updated: 2024/08/22 20:26:58 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_pipe_closing_child(t_cmd *cmd_data)
{
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
}
