/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 01:10:21 by jdach             #+#    #+#             */
/*   Updated: 2024/08/23 20:59:35 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_bin(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	char	*path;
	char	**args;
	int		execve_return;

	path = exe_bin_get_bin_path(cmd_list_item, cmd_data);
	args = exe_bin_args(cmd_list_item->arguments, cmd_list_item->binary);
	execve_return = execve(path, args, cmd_data->envp);
	free(path);
	free(args);
	if (execve_return == -1)
		exit (127);
}
