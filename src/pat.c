/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:41:03 by jdach             #+#    #+#             */
/*   Updated: 2024/07/16 18:22:46 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
- initialize history.
- start minishell loop.
- if there is input, add it to the history.
- else, print a new line.
*/

#include "minishell.h"
#include "../inc/parser.h"
void	TEST_printf_stuff(t_cmd_list **head);

void	pat(void)
{
	char	*input;
	t_token	*tokens;
	t_cmd_list *cmd_list;

	while (1)
	{
		input = readline(BLUE "Mini🐚 > " NS);
		if (*input)
		{
			add_history(input);
			tokens = tokenizer(input);
			cmd_list = parse_tokens(&tokens);
			if (cmd_list)
				TEST_printf_stuff(&cmd_list);
		}
		else
			write(1, "\n", 1);
	}
}


void	TEST_printf_stuff(t_cmd_list **head)
{
	t_cmd_list	*current;
	int i;

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
				ft_printf("	Argument %d: %s\n", i, current->arguments[i++]);
		}
		current = current->next;
	}
}
