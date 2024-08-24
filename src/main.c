/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:27:29 by paribeir          #+#    #+#             */
/*   Updated: 2024/08/24 10:52:45 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

/*
- initialize history.
- start minishell loop.
- if there is input, add it to the history.
- else, exit and cleanup (cleanup needs to be implemented).
*/

void	debug_print_cmds(t_cmd_list *cmd, int active)
{
	int			i;

	while (active != 0 && cmd)
	{
		i = -1;
		ft_printf("Type: %d\n", cmd->type);
		if (cmd->binary)
			ft_printf("	Binary: %s\n", cmd->binary);
		if (cmd->type != T_PIPE && cmd->type != AND_IF && cmd->type != OR_IF)
			while (cmd->arguments[++i])
				ft_printf("	Argument %d: %s\n", i, cmd->arguments[i]);
		cmd = cmd->next;
	}
}

void	minishell(t_cmd_list *cmd_list, t_cmd *cmd_data)
{
	char		*input;
	t_token		*tokens;

	exe_signals_default();
	input = readline(BLUE "Mini🐚 > " NS);
	if (input)
	{
		exe_signals_processing();
		add_history(input);
		tokens = tokenizer(input, cmd_data);
		cmd_list = parse_tokens(&tokens);
		debug_print_cmds(cmd_list, 0);
		exe(cmd_list, cmd_data);
		exe_cleanup_aftercmd(cmd_list);
	}
	else if (!input)
		exit(EXIT_SUCCESS);
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
	while (1)
		minishell(cmd_list, &cmd_data);
}
