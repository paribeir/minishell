/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:07:18 by paribeir          #+#    #+#             */
/*   Updated: 2024/07/16 16:48:41 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "parser.h"

//check mem management
void	expand_env_vars(t_token	*token)
{
	char *str;
	char *current;

	if (!ft_strchr(token->str, '\''))
		token->str = expand_heredoc(token->str);
	else
	{
		current = ft_strdup("");
		str = token->str;
		while (*str)
		{
			if (ft_strchr(str, '$') && !var_in_squote(str))
				add_expanded_var(&current, &str); //expand this var
			else
				add_literal(&current, &str); //copy everything inside single quotes
		}
		free(token->str);
		token->str = current; //overwrite token->str with new string. Do I need to alloc more memory?
	}
}

void	add_expanded_var(char **current, char **str)
{
	char	*var;
	char	*total;
    int     i;

	var = get_var(str); //TO DO: check if this advances the string past the var name
	if (var)
	{
		total = (char *)ft_calloc(strlen(*current) + strlen(var) + 1, sizeof(char));
		if (total)
		{
			ft_strlcpy(total, *current, strlen(*current) + strlen(var) + 1);
			ft_strlcat(total, var, strlen(*current) + strlen(var) + 1);
			free (*current);
			*current = total;
		}
		free (var);
	}
}

//make function usable for wildcard as well?
void	add_literal(char **current, char **str)
{
	char	*total;
	int	len;

	if (ft_strchr(*str, '\''))
		len = ft_strchr(*str, '\'') - *str;
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
	if (**str == '\'')
            (*str)++;
}

/*expand variable*/
char	*get_var(char **str)
{
	char	*var_name;
	char	*start;
	char	*var_content;

	(*str)++;
	start = *str;
	if (!start || (!ft_isalnum(*start) && *start != '_'))
		return ("$");
	while (**str && (ft_isalnum(**str) || **str == '_'))
		(*str)++;
	var_name = ft_substr(start + 1, 0, *str - (start + 1));
	if (!var_name)
		return (NULL);
	var_content = getenv(var_name);
	free(var_name);
	if (!var_content)
		return (ft_strdup(""));
	return (ft_strdup(var_content));
}
