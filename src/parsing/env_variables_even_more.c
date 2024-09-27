/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables_even_more.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:46:27 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/27 18:50:50 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//extracts the variable name from the heredoc string
char	*extract_var_name(char **str)
{
	char	*start;
	char	*var_name;

	while (**str && **str != '$')
		(*str)++;
	(*str)++;
	start = *str;
	if (start && start[0] == '?')
	{
		(*str)++;
		return (ft_strdup("?"));
	}
	else if (!start || (!ft_isalnum(*start) && *start != '_'))
		return (ft_strdup("$"));
	while (**str && (ft_isalnum(**str) || **str == '_'))
		(*str)++;
	var_name = ft_substr(start, 0, *str - start);

	return (var_name);
}

char	*get_var(char **str, t_cmd *cmd_data)
{
	char	*var_name;
	char	*var_content;

	var_name = extract_var_name(str);
	if (!var_name)
		return (NULL);
	var_content = get_var_content(var_name, cmd_data);
	free(var_name);
	return (var_content);
}
