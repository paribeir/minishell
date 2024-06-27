/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:37:53 by paribeir          #+#    #+#             */
/*   Updated: 2024/06/27 19:08:18 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/tokenizer.h"
#include "../inc/parser.h"

//how and when remove quotes?
//Don't remove quotes in heredoc
int	quotes_check(t_token *token)
{
	int	i;
	int	q_count;

	i = 0;
	q_count = 0;
	while (token->str[i])
	{
		if ((token->str[i] == '\'' || token->str[i] == '\"') \
		&& token->str[i + 1] && !(ft_strchr(&token->str[i + 1], &token->str[i])))
			return (ft_printf("Syntax error: Unclosed quotes\n"));
		if ()
	}

	return (0);
}

/*quotes_find_pair(token->str, &i, token->str[i])

int	quotes_find_pair(char *str, int *i, char q)
{
	(*i)++;
	while (str[*i] && str[*i] != q)
		(*i)++;
	if (str[*i] == q)
		return (0);
	return (1);
}*/
