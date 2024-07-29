/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:48:29 by jdach             #+#    #+#             */
/*   Updated: 2024/07/29 18:00:41 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_pipe_out(t_cmd *cmd_env)
{
	pipe(cmd_env->pipe);
	if (cmd_env->fdout_status == -1)
		dup2(cmd_env->pipe[1], STDOUT_FILENO);
	close(cmd_env->pipe[1]);
}
