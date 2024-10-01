/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:38:33 by paribeir          #+#    #+#             */
/*   Updated: 2024/10/01 22:01:46 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TO DO: Wildcard
/*if (strchr(current->str, '*'))
	expand_wildcards(current);*/
int	variable_expansion(t_token **head, t_cmd *cmd_data)
{
	t_token	*current;

	current = *head;
	while (current)
	{
		if (current->subtype == HEREDOC)
		{
			current->next->str = heredoc_handler(current, cmd_data);
			if (current->next->str == NULL || g_signum == SIGINT)
				return (free_tokens(head), head = NULL, g_signum = 0, 1);
		}
		else if (current->type == CMD_WORD && (!current->prev || \
		current->prev->subtype != HEREDOC))
		{
			if (ft_strchr(current->str, '$'))
				expand_env_vars(current, cmd_data);
			if (current->subtype == SQUOTE || \
			current->subtype == DQUOTE)
				quotes_remove(&current);
		}
		current = current->next;
	}
	return (0);
}
