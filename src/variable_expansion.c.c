/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:38:33 by paribeir          #+#    #+#             */
/*   Updated: 2024/07/04 22:01:29 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/tokenizer.h"
#include "../inc/parser.h"

void	variable_enxpansion(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current)
	{
		if (current->type == HEREDOC)
			current->next->str = heredoc_handler(current);
		else if (current->type == CMD_WORD)
		{
			//check for env_variables ($)
			//check for wildcards (*)
			//remove quotes
		}
		current = current->next;
	}
}
char	*expand_no_quotes(char *str)
{
	char	*sum;
	char	*before_var;

	sum = ft_strdup("");
	while (*str)
	{
		if (!ft_strchr(str, '$'))
		{
			sum = aux_str_join(sum, str);
			break ;
		}
		else
		{
			before_var = ft_substr(str, 0, ft_strchr(str, '$') - str);
			sum = aux_str_join(sum, before_var);
			sum = aux_str_join(sum, get_var(&str));
		}
		str = ft_strchr(str, '$') + 1;
	}
	return (sum);
}

char *aux_str_join(char *str1, char *str2)
{
	char *temp;

	temp = ft_strjoin(str1, str2);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (temp);
}

char	*get_var(char **str)
{
	char	*var_name;
	char	*start;
	char	*var_content;

	(*str)++;
	start = *str;
	while (**str && (ft_isalnum(**str) || **str == '_'))
		(*str)++;
	var_name = ft_substr(start, 0, *str - start);
	if (!var_name)
		return (NULL);
	var_content = getenv(var_name);
	free(var_name);
	if (!var_content)
		return (ft_strdup(""));
	return (ft_strdup(var_content));
}


/*When you call getenv(var_name), the returned string (var_content) 
points to static memory managed by the environment. 
If you directly return var_content, it could lead to issues 
if the caller attempts to modify or free this memory 
(which is not allowed and could cause undefined behavior).*/