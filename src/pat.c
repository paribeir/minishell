/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:41:03 by jdach             #+#    #+#             */
/*   Updated: 2024/07/09 00:07:02 by paribeir         ###   ########.fr       */
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

	current = *head;
	while (current)
	{
		ft_printf("%s		Arguments:%s Type: %d\n", current->binary, current->arguments[0], current->type);
		current = current->next;
	}
}