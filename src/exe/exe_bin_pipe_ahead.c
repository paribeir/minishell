/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bin_pipe_ahead.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:48:29 by jdach             #+#    #+#             */
/*   Updated: 2024/07/21 11:24:58 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_bin_pipe_ahead(t_cmd_list *cmd_list_item, t_cmd *cmd_env)
{
	if (cmd_list_item->next && cmd_list_item->next->type == T_PIPE)
	{
		pipe(cmd_env->pipe);
		dup2(cmd_env->pipe[1], STDOUT_FILENO);
		close(cmd_env->pipe[1]);
	}
}
