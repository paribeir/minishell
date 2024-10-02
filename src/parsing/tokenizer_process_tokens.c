/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_process_tokens.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:23:28 by patricia          #+#    #+#             */
/*   Updated: 2024/10/02 14:46:59 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_small(char *input, t_token *token, t_cmd *cmd_data)
{
	int	i;

	i = 0;
	if (input[i] == '|' && input[i + 1] != '|')
		token->type = PIPE;
	else if (input[i] == '<' || input[i] == '>')
		token->type = IO_FILE;
	else if (input[i] == '&' || input[i] == '|')
		token->type = OPERATOR;
	while (input[i + 1] && input[i] == input[i + 1])
		i++;
	if (i > 1)
	{
		ft_printf("minishell: syntax error near token \
		\'%c%c\'\n", input[0], input[1]);
		cmd_data->exit_code = 2;
		return (0);
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
			break ;
	}
	token->subtype = add_subtype(q, start);
	token->type = CMD_WORD;
	token->length = i;
	return (i);
}

void	add_token(char *start, t_token **head, t_token *token)
{
	token->str = (char *)ft_calloc(token->length + 1, sizeof(char));
	if (!token->str)
	{
		ft_putstr_fd("minishell: malloc error\n", STDERR_FILENO);
		return ;
	}
	ft_strlcpy(token->str, start, token->length + 1);
	token_add_back(head, token);
}
