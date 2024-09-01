/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patricia <patricia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:06:59 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/01 22:26:51 by patricia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(void)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
	{
		ft_printf("Malloc error in create_node\n");
		exit(EXIT_FAILURE);
	}
	new_token->type = 0;
	new_token->type = 0;
	new_token->str = ft_strdup("");
	new_token->length = 0;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	token_add_back(t_token **head, t_token *new_node)
{
	t_token	*temp;

	temp = *head;
	if (temp->type == 0)
		*head = new_node;
	else
	{
		while (temp->next)
			temp = temp->next;
	}
	temp->next = new_node;
	new_node->prev = temp;
}

int	add_subtype(char q, char *input)
{
	if (q == '\'')
		return (SQUOTE);
	else if (q == '\"')
		return (DQUOTE);
	else if (input[1] && input[0] == '<' && input[1] == '<')
		return (HEREDOC);
	else if (input[1] && input[0] == '>' && input[1] == '>')
		return (REDIR_APPEND);
	else if (q == '<')
		return (REDIR_IN);
	else if (q == '>')
		return (REDIR_OUT);
	else if (input[1] && q == '&' && input[1] == '&')
		return (AND_IF);
	else if (input[1] && q == '|' && input[1] == '|')
		return (OR_IF);
	else if (q == '|' && (!input[1] || (input[1] && input[1] != '|')))
		return (T_PIPE);
	return (0);
}

/*Small syntax check.
A simple command can either be one or many IO_FILE(s) or CMD_WORD(s), or both.
A pipe or operator must be followed by a IO_FILE or CMD_WORD
(no consecutive pipes or operators allowed)
Quotes must be closed*/
//TO DO--> error!
int	check_syntax(t_token **head)
{
	int	i;
	t_token	*current;

	i = 0;
	current = *head;
	while (current)
	{
		if (i == 0 && current->type < CMD_WORD)
			return (ft_printf("Syntax Error: a pipe or operator must be followed by either a cmd or redirect\n"));
		else if (current->type == IO_FILE && (!current->next || current->next->type != CMD_WORD))
			return (ft_printf("Syntax Error: redirect must be followed by FILE name bzw heredoc DELIMITER\n"));
		else if ((current->subtype == SQUOTE || current->subtype == DQUOTE) && quotes_check(current))
			return (ft_printf("Syntax Error: unclosed quotes\n"));
		if (current->type < CMD_WORD)
			i = 0;
		else
			i++;
		current = current->next;
	}
	return (0);
}
