/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:00:07 by paribeir          #+#    #+#             */
/*   Updated: 2024/06/18 18:22:03 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/tokenizer.h"
#include "../inc/parser.h"

void	eis_tee(t_token *token)
{
	t_eistee	*complete_cmd;

	complete_cmd = parse_list(token);
}

t_eistee	*parse_list(t_token *token)
{
	t_eistee	*left;
	t_eistee	*right;
	t_token		*copy;

	copy = token;
	go to end
	while(tokens)
		if token->type == OPERATOR
			
	else
		token = token->next;
	right = parse_pipe_sequence(token);

}


