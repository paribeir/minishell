/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:46:53 by jdach             #+#    #+#             */
/*   Updated: 2024/07/17 21:49:45 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_init_cmd_env(t_cmd *cmd_env)
{
	cmd_env->saved_stdin = dup(STDIN_FILENO);
	cmd_env->saved_stdout = dup(STDOUT_FILENO);
	cmd_env->saved_pipe_read_fd = -1;
	cmd_env->pipe[0] = -1;
	cmd_env->pipe[0] = -1;
}

void	exe_run(t_cmd_list	*cmd_list)
{
	t_cmd	cmd_env;

	exe_init_cmd_env(&cmd_env);
	while (cmd_list)
	{
		if (cmd_list->type == BINARY)
			exe_bin(cmd_list, &cmd_env);
		else if (cmd_list->type == HEREDOC)
			exe_here_doc(cmd_list, &cmd_env);
		else if (cmd_list->type == REDIR_IN)
			exe_redir_in(cmd_list, &cmd_env);
		else if (cmd_list->type == BLTIN_ECHO)
			exe_bltn_echo(cmd_list, &cmd_env);
		cmd_list = cmd_list->next;
	}
	while (wait(NULL) > 0)
		;
	dup2(cmd_env.saved_stdin, STDIN_FILENO);
	dup2(cmd_env.saved_stdout, STDOUT_FILENO);
	close(cmd_env.saved_stdin);
	close(cmd_env.saved_stdout);
}
