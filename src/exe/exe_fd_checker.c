/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_fd_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 01:10:21 by jdach             #+#    #+#             */
/*   Updated: 2024/08/29 00:06:47 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_fd_checker(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	t_token_subtype	type;
	int				err_printing;
	char			*file_path;

	err_printing = 1;
	type = cmd_list_item->type;
	while (cmd_list_item)
	{
		type = cmd_list_item->type;
		if (type == REDIR_IN || type == REDIR_APPEND)
		{
			file_path = cmd_list_item->arguments[0];
			if (access(file_path, F_OK) != 0 && err_printing == 1)
			{
				exe_err_long(ERR_FD_NO_SUCH_FILE);
				err_printing = 0;
			}
			if (access(file_path, R_OK) != 0 && err_printing == 1)
			{
				exe_err_long(ERR_FD_NOT_READABLE);
				err_printing = 0;
			}
		}
		else if (type == REDIR_OUT)
		{
			file_path = cmd_list_item->arguments[0];
			if (access(file_path, F_OK) == 0 && access(file_path, W_OK) != 0 && err_printing == 1)
			{
				exe_err_long(ERR_FD_NOT_WRITABLE);
				err_printing = 0;
			}
		}
		else if (type == T_PIPE)
			err_printing = 1;
		cmd_list_item = cmd_list_item->next;
	}
	(void)cmd_data;
}
