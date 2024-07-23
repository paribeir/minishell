/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:46:53 by jdach             #+#    #+#             */
/*   Updated: 2024/07/23 17:19:35 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_init_cmd_env(t_cmd *cmd_env, char *envp[])
{
	int	lines_n;
	int	i;

	lines_n = 0;
	i = -1;
	cmd_env->saved_stdin = dup(STDIN_FILENO);
	cmd_env->saved_stdout = dup(STDOUT_FILENO);
	cmd_env->pipe[0] = -1;
	cmd_env->pipe[0] = -1;
	while (envp[lines_n])
		lines_n++;
	cmd_env->envp = malloc(sizeof(char *) * (lines_n + 1));
	while (envp[++i])
		cmd_env->envp[i] = ft_strdup(envp[i]);
	cmd_env->envp[i] = NULL;
}

void	exe_run_map(t_cmd_list *cmd_list_item, t_cmd *cmd_env)
{
	t_token_subtype	t;

	t = cmd_list_item->type;
	if (t == BINARY)
		exe_bin(cmd_list_item, cmd_env);
	else if (t == HEREDOC || t == REDIR_IN || t == REDIR_OUT || \
	t == REDIR_APPEND || t == T_PIPE)
		exe_directs(cmd_list_item, cmd_env);
	else if (t == BLTIN_ECHO || t == BLTIN_CD || t == BLTIN_PWD || \
	t == BLTIN_EXPORT || t == BLTIN_UNSET || t == BLTIN_ENV || t == BLTIN_EXIT)
		exe_bltns(cmd_list_item, cmd_env);
}

void	exe_run(t_cmd_list	*cmd_list_item, char *envp[])
{
	t_cmd	cmd_env;

	exe_init_cmd_env(&cmd_env, envp);
	while (cmd_list_item)
	{
		exe_run_map(cmd_list_item, &cmd_env);
		cmd_list_item = cmd_list_item->next;
	}
	while (wait(NULL) > 0)
		;
	dup2(cmd_env.saved_stdin, STDIN_FILENO);
	close(cmd_env.saved_stdin);
	dup2(cmd_env.saved_stdout, STDOUT_FILENO);
	close(cmd_env.saved_stdout);
}
