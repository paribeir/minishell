/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:27:29 by paribeir          #+#    #+#             */
/*   Updated: 2024/10/02 16:27:10 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signum = 0;
void	banner(void);

void	setup_cmd_data(t_cmd *cmd_data)
{
	cmd_data->saved_stdin = dup(STDIN_FILENO);
	cmd_data->saved_stdout = dup(STDOUT_FILENO);
	cmd_data->exit_code = 0;
}

void	reset_cmd_data(t_cmd *cmd_data)
{
	close (cmd_data->saved_stdin);
	close (cmd_data->saved_stdout);
	cmd_data->saved_stdin = dup(STDIN_FILENO);
	cmd_data->saved_stdout = dup(STDOUT_FILENO);
	cmd_data->cmd_list_head = NULL;
	cmd_data->exit_codes = NULL;
}

void	check_g_signum(t_cmd *cmd_data)
{
	if (g_signum == SIGINT)
		cmd_data->exit_code = 130;
	else if (g_signum == SIGQUIT)
		cmd_data->exit_code = 131;
	g_signum = 0;
}

void	minishell(t_cmd_list *cmd_list, t_cmd *cmd_data)
{
	char		*input;
	t_token		*tokens;

	exe_signals_default();
	reset_cmd_data(cmd_data);
	input = readline(RED "MiniHell🔥 > " NS);
	if (input)
	{
		check_g_signum(cmd_data);
		exe_signals_processing();
		add_history(input);
		tokens = tokenizer(input, cmd_data);
		cmd_list = parse_tokens(&tokens, cmd_data);
		exe(cmd_list, cmd_data);
		exe_cleanup_aftercmd(cmd_data);
		free(input);
	}
	else if (!input)
	{
		write(1, "exit\n", 5);
		exe_cleanup(cmd_data);
		exit(EXIT_SUCCESS);
	}
	else
		write(1, "", 0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_cmd		cmd_data;
	t_cmd_list	*cmd_list;

	(void) argc;
	(void) argv;
	cmd_data.envp = exe_env_cpy(envp);
	cmd_list = NULL;
	exe_increase_shlvl(&cmd_data);
	setup_cmd_data(&cmd_data);
	while (1)
		minishell(cmd_list, &cmd_data);
}
