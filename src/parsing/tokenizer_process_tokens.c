/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_process_tokens.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:23:28 by patricia          #+#    #+#             */
/*   Updated: 2024/09/07 00:19:19 by paribeir         ###   ########.fr       */
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
		i += token_small(start, token);
	else
		i += token_big(start, token);
	add_token(start, &head, token);
	}
	if (check_syntax(&head))
		return (g_status = 2, NULL);
	if (head)
		variable_expansion(&head, cmd_data);
    return (head);
}

int	token_small(char *input, t_token *token)
{
	int	i;

	i = 0;
	if (input[i] == '|' && input[i + 1] != '|')
		token->type = PIPE;
	else if (input[i] == '<' || input[i] == '>')
		token->type = IO_FILE;
	else if (input[i] == '&' || input[i] == '|')
		token->type = OPERATOR;
	else
	{
		ft_printf("Syntax error: invalid chars\n");
		//exit (EXIT_FAILURE); //unrequired chars
	}
	while (input[i + 1] && input[i] == input[i + 1])
		i++;
	if (i > 1)
	{
		ft_printf("Syntax error: invalid operator\n");
		//exit (EXIT_FAILURE); //invalid operator
	}
	token->subtype = add_subtype(input[i], input);
	token->length = i + 1;
	return (i + 1);
}

int	token_big(char *start, t_token *token)
{
	int		i;
	char	q;

	i = 0;
	q = '\0';
	while (start[i])
	{
		while (start[i] && !ft_strchr(IFS"\"\'"SPECIAL_CHARS, start[i]))
			i++;
		if (start[i] && (start[i] == '\"' || start[i] == '\''))
		{
			q = start[i++];
			while (start[i] && start[i] != q)
				i++;
			if (start[i] == q)
				i++;
		}
		else
			break;
	}
	token->subtype = add_subtype(q, start); //idk if this make sense tbh
	token->type = CMD_WORD;
	token->length = i;
	return (i);
}

void	add_token(char *start, t_token **head, t_token *token)
{
	token->str = (char *)ft_calloc(token->length + 1, sizeof(char));
	if (!token->str)
	{
		ft_printf("malloc failed: token str\n");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(token->str, start, token->length + 1);
	token_add_back(head, token);
}
