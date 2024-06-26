/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:00:07 by paribeir          #+#    #+#             */
/*   Updated: 2024/06/26 13:55:44 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/tokenizer.h"
#include "../inc/parser.h"

t_cmd_list	*parse_tokens(t_token *token)
{
	t_token *current;
	t_cmd_list *node;

	current = token_fusion(token);
	if (!current)
		return (NULL);
	while (current)
	{
		node = create_ast_node(current);
	}
	node = create_ast_node(current);
	if (!head)
		return NULL;
	
	return (head);
}

t_token	*token_fusion(t_token	*token)
{
	if (token->type == IO_FILE && token->subtype != HEREDOC)
	{
		token->str = ft_strdup(token->next->str);

	}
	

}


void var_expansion(t_token *token)
{
	int	i;
	int	q_count;
	char	*new_str;

	i = 0;
	q_count = 0;
	if (token->subtype == SQUOTE || token->subtype == DQUOTE)
	{
		if (check_quotes(token))
			return (ft_print("Syntax error: unclosed quotes\n"));
		
	}

}

//how and when remove quotes?
int	check_quotes(t_token *token)
{
	int	i;
	int	q_count;

	i = 0;
	q_count = 0;
	while (token->str[i])
	{
		if (token->str[i] == '\'' || token->str[i] == '\"')
			q_count = count_quotes(token->str, &i, token->str[i]);
		//if (strchr(token->str, '$'))
		if (token->str[i] == '\'')
		{
			//IF (token->str[i]) AND sq_count % 2 == 0
				//DONT EXPAND, i++;
		}
		else 
			i++;
	}
	if (q_count % 2 != 0)
		return (1);
	return (0);
}

int	count_quotes(char *str, int *i, char q)
{
	int	q_count;

	q_count = 1;
	(*i)++;
	while (str[*i] && q_count % 2 != 0)
	{
		if (str[*i] == q)
			q_count++;
		(*i)++;
	}
	return (q_count);
}
