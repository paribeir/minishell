/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_directs_append.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:16:55 by jdach             #+#    #+#             */
/*   Updated: 2024/09/29 15:47:34 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_directs_append(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	int		fd;

	fd = 0;
	fd = open(cmd_list_item->arguments[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
	{
		perror("Minishell");
		cmd_data->stop_exe = 1;
		cmd_data->exit_code = 1;
		if (cmd_data->pipe_scenario == 1)
			exit (1);
		else
			return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
