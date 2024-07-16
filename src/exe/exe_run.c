/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:46:53 by jdach             #+#    #+#             */
/*   Updated: 2024/07/16 22:05:56 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_run(t_cmd_list	*cmd_list)
{
	t_cmd	cmd;

	while (cmd_list)
	{
		if (cmd_list->type == BINARY)
			exe_bin(cmd_list, &cmd);
		else if (cmd_list->type == HEREDOC)
			exe_here_doc(cmd_list, &cmd);
		else if (cmd_list->type == REDIR_IN)
			exe_redir_in(cmd_list, &cmd);
		else if (cmd_list->type == BLTIN_ECHO)
			exe_bltn_echo(cmd_list, &cmd);
		cmd_list = cmd_list->next;
	}
	while (wait(NULL) > 0)
		;
}
