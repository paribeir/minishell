/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:06:59 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/11 14:49:22 by paribeir         ###   ########.fr       */
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
		return (NULL);
	}
	new_token->type = 0;
	new_token->subtype = 0;
	new_token->str = NULL;
	new_token->length = 0;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	token_add_back(t_token **head, t_token *new_node)
{
	t_token	*temp;

	if (!head || !new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		new_node->prev = NULL;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
		new_node->prev = temp;
	}
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

/*Small syntax check:
1. A simple command can either be one or many IO_FILE(s) or CMD_WORD(s), or both.
2. A pipe or operator must be followed by a IO_FILE or CMD_WORD
(no consecutive pipes or operators allowed).
3. Quotes must be closed.*/
int	token_check_syntax(t_token **head)
{
	int	i;
	t_token	*current;

	i = 0;
	current = *head;
	while (current)
	{
		if ((i == 0 && current->type < CMD_WORD) || (current->type == IO_FILE && 
		(!current->next || current->next->type != CMD_WORD)))
			return (ft_printf("minishell: syntax error after \'%s\' token\n",
			 current->str), free_tokens(head), 1);
		else if ((current->subtype == SQUOTE || current->subtype == DQUOTE) &&
		quotes_check(current))
			return (free_tokens(head),
			ft_printf("minishell: syntax error (unclosed quotes)\n"));
		if (current->type < CMD_WORD)
			i = 0;
		else
			i++;
		current = current->next;
	}
	return (0);
}
