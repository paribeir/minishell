/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:46:53 by jdach             #+#    #+#             */
/*   Updated: 2024/07/21 14:28:44 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_init_cmd_env(t_cmd *cmd_env)
{
	cmd_env->saved_stdin = dup(STDIN_FILENO);
	cmd_env->saved_stdout = dup(STDOUT_FILENO);
	cmd_env->pipe[0] = -1;
	cmd_env->pipe[0] = -1;
}

void	exe_run(t_cmd_list	*c)
{
	t_cmd	cmd_env;

	exe_init_cmd_env(&cmd_env);
	while (c)
	{
		if (c->type == BINARY)
			exe_bin(c, &cmd_env);
		else if (c->type == HEREDOC || c->type == REDIR_IN || c->type == \
		REDIR_OUT || c->type == REDIR_APPEND || c->type == T_PIPE)
			exe_directs(c, &cmd_env);
		else if (c->type == BLTIN_ECHO)
			exe_bltn_echo(c, &cmd_env);
		c = c->next;
	}
	while (wait(NULL) > 0)
		;
	dup2(cmd_env.saved_stdin, STDIN_FILENO);
	dup2(cmd_env.saved_stdout, STDOUT_FILENO);
	close(cmd_env.saved_stdin);
	close(cmd_env.saved_stdout);
}
