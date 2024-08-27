/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_directs_redir_in.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:16:55 by jdach             #+#    #+#             */
/*   Updated: 2024/08/26 21:54:44 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_directs_redir_in(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	int		fd;

	fd = open(cmd_list_item->arguments[0], O_RDONLY);
	if (fd == -1)
	{
		exe_err_long(ERR_NO_SUCH_FILE);
		cmd_data->stop_exe = 1;
		g_status = 1;
		if (cmd_data->pipe_scenario == 1)
			exit (1);
		else
			return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}
