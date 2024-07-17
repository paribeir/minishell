/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 01:10:21 by jdach             #+#    #+#             */
/*   Updated: 2024/07/17 10:26:21 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**set_execve_args(char **original_args, char *binary)
{
	int		i;
	int		j;
	char	**execve_args;

	i = 0;
	j = 0;
	while (original_args[i] != NULL)
		i++;
	execve_args = (char **)malloc((i + 2) * sizeof(char *));
	execve_args[j++] = binary;
	while (j <= i)
	{
		execve_args[j] = original_args[j - 1];
		j++;
	}
	execve_args[j] = NULL;
	return (execve_args);
}

void	exe_bin(t_cmd_list *cmd_list_item, t_cmd *cmd)
{
	char	*path;
	char	**args;
	int		pid;

	exe_get_in_out(cmd_list_item, cmd);
	path = exe_get_bin_path(cmd_list_item);
	args = set_execve_args(cmd_list_item->arguments, cmd_list_item->binary);
	pid = fork();
	if (pid == 0)
		execve(path, args, NULL);
}
