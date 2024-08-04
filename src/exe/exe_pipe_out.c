/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:48:29 by jdach             #+#    #+#             */
/*   Updated: 2024/08/04 10:07:39 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_pipe_out(t_cmd *cmd_data)
{
	pipe(cmd_data->pipe);
	if (cmd_data->fdout_status == -1)
		dup2(cmd_data->pipe[1], STDOUT_FILENO);
	close(cmd_data->pipe[1]);
}
