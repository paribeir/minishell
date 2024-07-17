/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_get_in_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:17:44 by jdach             #+#    #+#             */
/*   Updated: 2024/07/17 18:03:48 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_get_out(t_cmd_list *cmd_list_item, t_cmd *cmd_env)
{
	if (cmd_list_item->next && cmd_list_item->next->type == T_PIPE)
	{
		if (cmd_env->saved_pipe_read_fd != -1)
			cmd_env->saved_pipe_read_fd = cmd_env->pipe[0];
		pipe(cmd_env->pipe);
		dup2(cmd_env->pipe[1], STDOUT_FILENO);
		close(cmd_env->pipe[1]);
	}
	else
		dup2(cmd_env->saved_stdout, STDOUT_FILENO);
}

void	exe_get_in(t_cmd_list *cmd_list_item, t_cmd *cmd_env)
{
	if (cmd_list_item->prev && cmd_list_item->prev->type == T_PIPE)
	{
		dup2(cmd_env->pipe[0], STDIN_FILENO);
		close(cmd_env->pipe[0]);
	}
	else
		dup2(cmd_env->saved_stdin, STDIN_FILENO);
}

void	exe_get_in_out(t_cmd_list *cmd_list_item, t_cmd *cmd_env)
{
	exe_get_out(cmd_list_item, cmd_env);
	exe_get_in(cmd_list_item, cmd_env);
}
