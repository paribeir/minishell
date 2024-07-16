/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:38:33 by paribeir          #+#    #+#             */
/*   Updated: 2024/07/16 17:07:20 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "parser.h"

//TO DO: Wildcard
void	variable_expansion(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current) 
	{
		if (current->subtype == HEREDOC)
			current->next->str = heredoc_handler(current);
		else if (current->type == CMD_WORD && current->prev->subtype != HEREDOC)
		{
			if (strchr(current->str, '$')) //check for env_variables ($)
				expand_env_vars(current);
			/*if (strchr(current->str, '*')) //check for wildcards (*)
				expand_wildcards(current);*/
			else if (current->subtype == SQUOTE || current->subtype == DQUOTE) //remove quotes
				quotes_remove(&current);
		}
		current = current->next;
	}
}
