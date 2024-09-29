/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bltns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:50:14 by jdach             #+#    #+#             */
/*   Updated: 2024/09/29 15:46:47 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_bltns(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	if (cmd_list_item->type == BLTIN_ECHO)
		exe_bltns_echo(cmd_list_item, cmd_data);
	else if (cmd_list_item->type == BLTIN_ENV)
		exe_bltns_env(cmd_data->envp, cmd_data);
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
