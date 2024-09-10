/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:07:18 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/10 12:46:42 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check mem management
void	expand_env_vars(t_token	*token, t_cmd *cmd_data)
{
	char	*str;
	char	*current;

	if (!ft_strchr(token->str, '\''))
		current = expand_heredoc(token->str, cmd_data);
	else
	{
		str = token->str;
		if (ft_strchr(str, '$') && !var_in_squote(str))
			current = expand_heredoc(str, cmd_data);
		else
			add_literal(&current, &str);
	}
	free(token->str);
	token->str = current;
}

void	add_expanded_var(char **current, char **str, t_cmd *cmd_data)
{
	char	*var;
	char	*total;

	var = get_var(str, cmd_data);
	if (var)
	{
		total = (char *)ft_calloc(strlen(*current) + strlen(var) + 1, sizeof(char));
		if (total)
		{
			ft_strlcpy(total, *current, ft_strlen(*current) + ft_strlen(var) + 1);
			ft_strlcat(total, var, ft_strlen(*current) + ft_strlen(var) + 1);
			free (*current);
			*current = total;
		}
		//free (var);
	}
}

//make function usable for wildcard as well?
void	add_literal(char **current, char **str)
{
	char	*total;
	int		i;

	total = (char *)ft_calloc(ft_strlen(*str), 1);
	i = 0;
	if (**str == '\'')
		(*str)++;
	while (**str && **str != '\'')
	{
		total[i++] = **str;
		(*str)++;
	}
	if (**str && **str == '\'')
		(*str)++;
	total[i] = '\0';
	*current = total;
}

/*If '$' is followed by a '?', it will be expanded into the exit status of the last foreground process.
If there are more characters after the '?', they are kept as is, not affecting the expansion.
e.g. $?hello --> 0hello*/
char	*get_var(char **str, t_cmd *cmd_data)
{
	char	*var_name;
	char	*start;
	char	*var_content;
	char	*result;

	(*str)++;
	start = *str;
	if (start && start[0] == '?')
	{
		(*str)++;
		result = ft_itoa(g_status);
		if (!result)
			return (NULL);
		return (result); //to be freed if called
	}
	else if (!start || (!ft_isalnum(*start) && *start != '_'))
		return (ft_strdup("$"));
	while (**str && (ft_isalnum(**str) || **str == '_'))
		(*str)++;
	var_name = ft_substr(start, 0, *str - start);
	if (!var_name)
		return (NULL);
	var_content = exe_env_get_var(var_name, cmd_data);
	free(var_name);
	if (!var_content)
		return (ft_strdup(""));
	result = ft_strdup(var_content);
	free(var_content);
	return (result);  //to be freed if called
}
