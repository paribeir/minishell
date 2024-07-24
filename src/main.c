/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:27:29 by paribeir          #+#    #+#             */
/*   Updated: 2024/07/24 16:07:55 by jdach            ###   ########.fr       */
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


int	main(int argc, char *argv[], char *envp[])
{
	char		*input;
	t_token		*tokens;
	t_cmd_list	*cmd_list;
	t_cmd		cmd_env;

	exe_init(&cmd_env, envp);
	while (1)
	{
		input = readline(BLUE "Mini🐚 > " NS);
		if (*input)
		{
			add_history(input);
			tokens = tokenizer(input);
			cmd_list = parse_tokens(&tokens);
			if (cmd_list && (argc > 1 && ft_strncmp(argv[1], "pat", 3) == 0))
				TEST_printf_stuff(&cmd_list);
			else
			{
				TEST_printf_stuff(&cmd_list);
				exe(cmd_list, &cmd_env);
			}
		}
		else
			write(1, "\n", 1);
	}
}
