/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_without_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 08:14:56 by jdach             #+#    #+#             */
/*   Updated: 2024/08/30 08:18:55 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_without_pipes(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	int				pid;
	t_token_subtype	t;

	exe_set_in_out(cmd_list_item, cmd_data);
	while (cmd_list_item && cmd_data->stop_exe == -1)
	{
		t = cmd_list_item->type;
		if (t == BINARY)
		{
			pid = fork();
			if (pid == 0)
				exe_bin(cmd_list_item, cmd_data);
		}
		else if (t == BLTIN_ECHO || t == BLTIN_CD || t == BLTIN_PWD || \
		t == BLTIN_EXPORT || t == BLTIN_UNSET || t == BLTIN_ENV || \
		t == BLTIN_EXIT)
			exe_bltns(cmd_list_item, cmd_data);
		cmd_list_item = cmd_list_item->next;
	}
}
