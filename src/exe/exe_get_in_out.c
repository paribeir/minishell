/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_get_in_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:17:44 by jdach             #+#    #+#             */
/*   Updated: 2024/07/17 21:41:34 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_get_in(t_cmd_list *cmd_list_item, t_cmd *cmd_env)
{
	if (cmd_list_item->prev && cmd_list_item->prev->type == T_PIPE)
	{
		dup2(cmd_env->pipe[0], STDIN_FILENO);
		close(cmd_env->pipe[0]);
	}
	else if (cmd_list_item->prev && (cmd_list_item->prev->type == HEREDOC || \
	cmd_list_item->prev->type == REDIR_IN))
		;
	else
		dup2(cmd_env->saved_stdin, STDIN_FILENO);
}

void	exe_get_out(t_cmd_list *cmd_list_item, t_cmd *cmd_env)
{
	int		fd;

	if (cmd_list_item->next && cmd_list_item->next->type == T_PIPE)
	{
		pipe(cmd_env->pipe);
		dup2(cmd_env->pipe[1], STDOUT_FILENO);
		close(cmd_env->pipe[1]);
	}
	else if (cmd_list_item->next && cmd_list_item->next->type == REDIR_OUT)
	{
		fd = open(cmd_list_item->next->arguments[0], \
		O_WRONLY | O_CREAT | O_TRUNC, 0666);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
		dup2(cmd_env->saved_stdout, STDOUT_FILENO);
}

void	exe_get_in_out(t_cmd_list *cmd_list_item, t_cmd *cmd_env)
{
	exe_get_in(cmd_list_item, cmd_env);
	exe_get_out(cmd_list_item, cmd_env);
}
