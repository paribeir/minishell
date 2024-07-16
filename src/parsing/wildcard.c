/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:02:00 by paribeir          #+#    #+#             */
/*   Updated: 2024/07/16 20:23:27 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	expand_wildcards(t_token *token)
{
	char *str;
	char *current;
	char	c;

	current = ft_strdup("");
	str = token->str;
	while (*str)
	{
		if (!wild_in_quote(token, &c))
			pathname_expansion(&current, &str); //pathname expansion
		else
			add_wild_literal(&current, &str, c);//copy
	}
	free(token->str);
	token->str = current; //overwrite token->str with new string
}

void 	pathname_expansion(char **current, char **str)
{

}

void	add_wild_literal(char **current, const char **str, char c)
{
	char	*total;
	char	*next_quote;
	int	len;

	if (c && ft_strchr(*str, c))
		len = ft_strchr(*str, c) - *str;
	else
		len = strlen(*str);
	total = ft_calloc(strlen(*current) + len + 1, sizeof(char));
	if (total)
	{
		ft_strlcpy(total, *current, len);
		ft_strlcat(total, *str, len);
		free (*current);
		*current = total;
		*str += len;
	}
	if (c && **str == c)
            (*str)++;
} */
