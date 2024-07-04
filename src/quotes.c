/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:37:53 by paribeir          #+#    #+#             */
/*   Updated: 2024/07/04 22:07:37 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/tokenizer.h"
#include "../inc/parser.h"

/*If we find a quote, we look for its pair.
If there is no pair, return 1.
If all quotes have pairs (are closed), return 0*/
int	quotes_check(t_token *token)
{
	int	i;

	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '\'' || token->str[i] == '\"' \
		&& quotes_find_pair(token->str, &i, token->str[i]))
			return (1);
		else
			i++;
	}
	return (0);
}

//&& token->str[i + 1] && !(ft_strchr(&token->str[i + 1], token->str[i])))		

/*Advance in the string until it finds a matching quote (q).
Return 0 on success, return 1 on failure.*/
int	quotes_find_pair(char *str, int *i, char q)
{
	(*i)++;
	while (str[*i] && str[*i] != q)
		(*i)++;
	if (str[*i] && str[*i] == q)
		return (0);
	return (1);
}

//TO DO--> Handle malloc error
void	quotes_remove(t_token *token)
{
	int	i;
	int j;
	char *new_str;
	int	in_squote;
	int	in_dquote;

	new_str = (char *)ft_calloc(ft_strlen(token->str) + 1, sizeof(char));
	if (!new_str)
		ft_printf("Malloc error in quote removal\n");
	i = 0;
	j = 0;
	in_squote = 0;
	in_dquote = 0;
	while (token->str[i])
	{
		if (token->str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (token->str[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		else
			new_str[j++] = token->str[i];
		i++;
	}
	ft_strlcpy(token->str, new_str, ft_strlen(token->str) + 1);
	free (new_str);
}
