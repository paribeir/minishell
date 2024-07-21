/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bltns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:50:14 by jdach             #+#    #+#             */
/*   Updated: 2024/07/21 16:00:01 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_bltns(t_cmd_list *cmd_list_item, t_cmd *cmd_env)
{
	exe_bin_pipe_ahead(cmd_list_item, cmd_env);
	if (cmd_list_item->type == BLTIN_ECHO)
		exe_bltns_echo(cmd_list_item, cmd_env);
	dup2(cmd_env->saved_stdout, STDOUT_FILENO);
	dup2(cmd_env->saved_stdin, STDIN_FILENO);
}
