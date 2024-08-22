/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bltns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:50:14 by jdach             #+#    #+#             */
/*   Updated: 2024/08/22 17:54:42 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_bltns_map(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	if (cmd_list_item->type == BLTIN_ECHO)
		exe_bltns_echo(cmd_list_item, cmd_data);
	else if (cmd_list_item->type == BLTIN_ENV)
		exe_bltns_env(cmd_data->envp);
	else if (cmd_list_item->type == BLTIN_PWD)
		exe_bltns_pwd(cmd_list_item, cmd_data);
	else if (cmd_list_item->type == BLTIN_CD)
		exe_bltns_cd(cmd_list_item, cmd_data);
	else if (cmd_list_item->type == BLTIN_EXPORT)
		exe_bltns_export(cmd_list_item, cmd_data);
	else if (cmd_list_item->type == BLTIN_UNSET)
		exe_bltns_unset(cmd_list_item, cmd_data);
	else if (cmd_list_item->type == BLTIN_EXIT)
		exe_bltns_exit(cmd_list_item, cmd_data);
}

void	exe_bltns(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	int		pid;

	if (cmd_data->wr_to_pipe == 1)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(cmd_data->pipe[1], STDOUT_FILENO);
			exe_bltns_map(cmd_list_item, cmd_data);
			exit(EXIT_SUCCESS);
		}
	}
	else
		exe_bltns_map(cmd_list_item, cmd_data);
}
