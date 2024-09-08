/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:38:33 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/08 20:08:24 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TO DO: Wildcard
void	variable_expansion(t_token **head, t_cmd *cmd_data)
{
	t_token	*current;

	current = *head;
	while (current)
	{
		if (current->subtype == HEREDOC)
			current->next->str = heredoc_handler(current, cmd_data);
		else if (current->type == CMD_WORD && (!current->prev || current->prev->subtype != HEREDOC))
		{
			if (strchr(current->str, '$')) //check for env_variables ($)
				expand_env_vars(current, cmd_data);
			/*if (strchr(current->str, '*')) //check for wildcards (*)
				expand_wildcards(current);*/
			if (current->subtype == SQUOTE || current->subtype == DQUOTE) //remove quotes
				quotes_remove(&current);
		}
		current = current->next;
	}
}
