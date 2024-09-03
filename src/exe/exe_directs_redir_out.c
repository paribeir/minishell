/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_directs_redir_out.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:06:19 by jdach             #+#    #+#             */
/*   Updated: 2024/09/02 17:31:30 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_directs_redir_out(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	int	fd;

	fd = open(cmd_list_item->arguments[0], \
	O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		cmd_data->stop_exe = 1;
		g_status = 1;
		perror("Minishell");
		if (cmd_data->pipe_scenario == 1)
			exit (1);
		else
			return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
