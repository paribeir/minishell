/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_get_exit_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:18:56 by jdach             #+#    #+#             */
/*   Updated: 2024/08/30 19:01:22 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_get_exit_status_piped(pid_t pid, int status, t_cmd *cmd_data)
{
	t_exit_status	*list_item;
	t_exit_status	*last_exit_status;
	t_list			*exit_codes;

	while (pid > 0)
	{
		if (WIFEXITED(status))
		{
			exit_codes = cmd_data->exit_codes;
			while (exit_codes != NULL)
			{
				list_item = exit_codes->content;
				if (list_item->pid == pid)
				{
					list_item->exit_status = WEXITSTATUS(status);
					break ;
				}
				exit_codes = exit_codes->next;
			}
		}
		pid = wait(&status);
	}
	last_exit_status = ft_lstlast(cmd_data->exit_codes)->content;
	g_status = last_exit_status->exit_status;
}

/******************************  INFO ******************************************
We need to get the exit status of the child processes. However in a pipe
scenario we cannot be certain, that the last child process to finish is actually
the one that we need to get the exit status from – as it may not be the last
one in the list of commands. So in a pipe scenario we have previously
stored all the child pids in a linked list. Here when we listen for the children
to signal their termination, we store their exit status in the matching entry
of the stored processes via pid. Later we will only set the last item of that
list as the global exit status.
In a non pipe scenario we simply listen for the only child process that may
come since only one child process is possible.
*/

void	exe_get_exit_status(t_cmd *cmd_data)
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	if (cmd_data->pipe_scenario == 1)
		exe_get_exit_status_piped(pid, status, cmd_data);
	else
	{
		while (pid > 0)
		{
			if (WIFEXITED(status))
				g_status = WEXITSTATUS(status);
			pid = wait(&status);
		}
	}
}
