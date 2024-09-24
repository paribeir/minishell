/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:06:04 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/11 11:31:59 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*self-written errors dont have specific error codes*/
t_token	*process_tokens(char *input, t_token *head, t_cmd *cmd_data)
{
	t_token *token;
	size_t i;
	char *start;

	i = 0;
	while (input[i])
	{
		while (input[i] && ft_strchr(IFS, input[i]))
			i++;
		if (!input[i])
			break;
		token = create_token();
		start = &input[i];
		if (ft_strchr(SPECIAL_CHARS, input[i]))
		{
			if (token_small(start, token))
				i += token_small(start, token);
			else
			{
				free (token);
				free_tokens(&head);
				return (NULL); //mem leaks
			}
		}
		else
			i += token_big(start, token);
		add_token(start, &head, token);
	}
	if (token_check_syntax(&head)) //mem leaks
		return (g_status = 2, NULL);
	if (head)
		variable_expansion(&head, cmd_data);
    return (head);
}

/*
The tokenizer's role is to break the input into meaningful tokens:
- Assigns each lexeme of the input string into a token;
- Checks syntax;
- Returns head of linked list on success, NULL on failure.
*/
t_token	*tokenizer(char *input, t_cmd *cmd_data)
{
	t_token	*head;
	size_t	i;

	i = 0;
	head = NULL;
	if (input[i])
		head = process_tokens(&input[i], head, cmd_data);
	return (head);
}
