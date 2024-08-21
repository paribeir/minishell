/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 01:10:21 by jdach             #+#    #+#             */
/*   Updated: 2024/08/21 19:27:28 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_bin(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	char	*path;
	char	**args;
	int		pid;

	path = exe_bin_get_bin_path(cmd_list_item, cmd_data);
	args = exe_bin_args(cmd_list_item->arguments, cmd_list_item->binary);
	pid = fork();
	if (pid == 0)
	{
		if (cmd_data->pipe_status[0] == 1)
			dup2(cmd_data->pipe[0], STDIN_FILENO);
		if (cmd_data->pipe_status[1] == 1)
			dup2(cmd_data->pipe[1], STDOUT_FILENO);
		if (execve(path, args, cmd_data->envp) == -1)
		{
			free(path);
			free(args);
			exit (127);
		}
	}
	free(path);
	free(args);
}
