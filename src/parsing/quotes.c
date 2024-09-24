/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:37:53 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/15 18:47:48 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*If we find a quote, we look for its pair.
If there is no pair, return 1.
If all quotes have pairs (are closed), return 0*/
int	quotes_check(t_token *token)
{
	int	i;

	i = 0;
	while (token->str[i])
	{
		if ((token->str[i] == '\'' || token->str[i] == '\"') \
		&& quotes_find_pair(token->str, &i, token->str[i]))
			return (1);
		i++;
	}
	return (0);
}

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

/*is the env variable ($) inside single quotes?
if there is a '$' inside single quotes, return 1. Otherwise, return 0*/
int	var_in_squote(char *str)
{
	int	i;
	int	in_squote;
	int	in_dquote;

	i = 0;
	in_squote = 0; //false
	in_dquote = 0; //false
	while (str && str[i])
	{
		if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		if (str[i] == '$')
			return (in_squote);
		i++;
	}
	return (0);
}

int	all_var_in_squote(char *str)
{
	while (str)
	{
		if (var_in_squote(str))
			return (1);
		else if (ft_strchr(str + 1, '$'))
			str = ft_strchr(str, '$');
		else
			break ;
	}
	return (0);
}

//is the wildcard (*) inside any quotes?
/*
int	wild_in_quote(char *str, char *c)
{
	int	i;
	int	in_squote;
	int	in_dquote;

	i = 0;
	in_squote = 0; //false
	in_dquote = 0; //false
	while (str[i])
	{
		if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		if (str[i] == '*')
		{
			if (in_squote)
				*c = '\'';
			else if (in_dquote)
				*c = '\"';
			return (in_squote || in_dquote); //id there is a '*' inside any quotes, it returns 1. Otherwise it returns 0.
		}
		i++;
	}
	return (0);
}*/
