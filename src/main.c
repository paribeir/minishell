/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:27:29 by paribeir          #+#    #+#             */
/*   Updated: 2024/08/17 23:05:00 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
- initialize history.
- start minishell loop.
- if there is input, add it to the history.
- else, exit and cleanup (cleanup needs to be implemented).
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

int	main(int argc, char *argv[], char *envp[])
{
	char		*input;
	t_token		*tokens;
	t_cmd_list	*cmd_list;
	t_cmd		cmd_data;

	(void) argc;
	(void) argv;
	cmd_list = NULL;
	cmd_data.envp = exe_env_cpy(envp);
	while (1)
	{
		exe_signals_default(cmd_list, &cmd_data);
		input = readline(BLUE "Mini🐚 > " NS);
		if (input)
		{
			exe_signals_processing(cmd_list, &cmd_data);
			add_history(input);
			tokens = tokenizer(input, &cmd_data);
			cmd_list = parse_tokens(&tokens);
			// TEST_printf_stuff(&cmd_list);
			exe(cmd_list, &cmd_data);
		}
		else if (!input)
			exit(EXIT_SUCCESS);
		else
			write(1, "", 0);
	}
}
