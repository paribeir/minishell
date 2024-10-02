/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:06:04 by paribeir          #+#    #+#             */
/*   Updated: 2024/10/02 14:00:54 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*process_single_token(char *input, t_token *head, \
t_cmd *cmd_data, size_t *i)
{
	t_token	*token;
	char	*start;

	while (input[*i] && ft_strchr(IFS, input[*i]))
		(*i)++;
	if (!input[*i])
		return (head);
	token = create_token();
	start = &input[*i];
	if (ft_strchr(SPECIAL_CHARS, input[*i]))
	{
		if (token_small(start, token, cmd_data))
			*i += token_small(start, token, cmd_data);
		else
			return (free(token), free_tokens(&head), NULL);
	}
	else
		*i += token_big(start, token);
	add_token(start, &head, token);
	return (head);
}

t_token	*process_tokens(char *input, t_token *head, t_cmd *cmd_data)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		head = process_single_token(input, head, cmd_data, &i);
		if (!head)
			return (NULL);
	}
	if (token_check_syntax(&head))
		return (cmd_data->exit_code = 2, NULL);
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
