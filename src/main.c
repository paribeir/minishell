/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:27:29 by paribeir          #+#    #+#             */
/*   Updated: 2024/08/16 18:32:49 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
- initialize history.
- start minishell loop.
- if there is input, add it to the history.
- else, print a new line.
*/

void	TEST_printf_stuff(t_cmd_list **head)
{
	t_cmd_list	*current;
	int			i;

	current = *head;
	while (current)
	{
		i = 0;
		ft_printf("Type: %d\n", current->type);
		if (current->binary)
			ft_printf("	Binary: %s\n", current->binary);
		if (current->type != T_PIPE && current->type != AND_IF && current->type != OR_IF)
		{
			while (current->arguments[i])
			{
				ft_printf("	Argument %d: %s\n", i, current->arguments[i]);
				i++;
			}
		}
		current = current->next;
	}
}

void	init_cmd_data(t_cmd *cmd_data, char *envp[])
{
	cmd_data->envp = exe_env_cpy(envp);
	cmd_data->saved_stdin = dup(STDIN_FILENO);
	cmd_data->saved_stdout = dup(STDOUT_FILENO);
	cmd_data->pipe[0] = -1;
	cmd_data->pipe[0] = -1;
	cmd_data->pipe_status = -1;
	cmd_data->fdout_status = -1;
	cmd_data->exit_status = 0;
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*input;
	t_token		*tokens;
	t_cmd_list	*cmd_list;
	t_cmd		cmd_data;

	init_cmd_data(&cmd_data, envp);
	while (1)
	{
		exe_signals_responsive(cmd_list, &cmd_data);
		input = readline(BLUE "Mini🐚 > " NS);
		if (*input)
		{
			add_history(input);
			tokens = tokenizer(input, &cmd_data);
			cmd_list = parse_tokens(&tokens);
			if (cmd_list && (argc > 1 && ft_strncmp(argv[1], "pat", 3) == 0))
				TEST_printf_stuff(&cmd_list);
			else
			{
				TEST_printf_stuff(&cmd_list);
				exe(cmd_list, &cmd_data);
			}
		}
		else
			write(1, "\n", 1);
	}
}
