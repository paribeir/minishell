/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:41:37 by paribeir          #+#    #+#             */
/*   Updated: 2024/06/20 16:09:23 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/tokenizer.h"
#include "../inc/parser.h"

/* Start AST */
t_ast	*create_ast(t_token *token)
{
    t_token *tail;

    tail = get_tail(token);
    if (!tail)
        return (NULL);
	return (parse_tokens(tail, OPERATOR));
}

t_ast *create_ast_node(t_token *token) 
{
    t_ast   *node;
    
    node = (t_ast *)malloc(sizeof(t_ast));
    if (!node)
        return NULL;
    node->type = token->type;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

/*This function returns a pointer to the token with the type that we are looking for.
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
