/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 01:10:21 by jdach             #+#    #+#             */
/*   Updated: 2024/07/29 17:42:32 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_bin(t_cmd_list *cmd_list_item, t_cmd *cmd_env)
{
	char	*path;
	char	**args;
	int		pid;

	path = exe_bin_get_bin_path(cmd_list_item, cmd_env);
	args = exe_bin_args(cmd_list_item->arguments, cmd_list_item->binary);
	pid = fork();
	if (pid == 0)
		execve(path, args, cmd_env->envp);
	dup2(cmd_env->saved_stdout, STDOUT_FILENO);
	dup2(cmd_env->saved_stdin, STDIN_FILENO);
}
