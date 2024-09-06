/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:06:04 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/07 00:07:50 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	init_tokens(input, &i, &head);
	if (input[i])
		head = process_tokens(&input[i], head, cmd_data);
	return (head);
}

/*skips whitespace, creates and initializes tokens*/
void	init_tokens(char *input, size_t *i, t_token **head)
{
	while (input[*i] && ft_strchr(IFS, input[*i]))
		(*i)++;
	if (input[*i])
		*head = create_token();
}
