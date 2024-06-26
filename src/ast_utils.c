/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:41:37 by paribeir          #+#    #+#             */
/*   Updated: 2024/06/25 22:19:02 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/tokenizer.h"
#include "../inc/parser.h"

/* Start AST */
t_cmd_list	*create_list(t_token *token)
{
    t_token *tail;

    tail = get_tail(token);
    if (!tail)
        return (NULL);
	return (parse_tokens(tail, OPERATOR));
}

t_cmd_list	*create_node(t_token *token) 
{
    t_cmd_list	*node;
    
    node = (t_cmd_list	*)malloc(sizeof(t_cmd_list));
    if (!node)
        return NULL;
    node->type = token->type;
    node->subtype = token->subtype;
    node->cmd_word = token->str;
    node->arguments = NULL;
    node->flags = NULL;
    node->prev = NULL;
    node->next = NULL;
    return (node);
}

/*this function returns a pointer to the token with the type that we are looking for.
We search from right to left.*/
t_token *get_type(t_token *token, t_token_type type)
{
    t_token *temp;
    int delimiter;

    temp = token;
    delimiter = type - 1;
    while (temp)
    {
        if (temp->type == type)
            return (temp);
        else if (temp->type == delimiter)
            break;
        temp = temp->prev;
    }
    return (NULL);
}

t_token *get_tail(t_token *token)
{
    t_token *temp;

    temp = token;
    while (temp && temp->next)
    {
        temp = temp->next;
    }
    return (temp);
}
