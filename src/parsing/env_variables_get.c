/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables_get.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:46:27 by paribeir          #+#    #+#             */
/*   Updated: 2024/10/02 14:55:54 by paribeir         ###   ########.fr       */
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

//gets the variable content by name and returns it (heredoc)
char	*get_var_content(char *var_name, t_cmd *cmd_data)
{
	char	*var_content;
	char	*result;

	if (var_name[0] == '?')
	{
		result = ft_itoa(cmd_data->exit_code);
		return (result);
	}
	var_content = exe_env_get_var(var_name, cmd_data);
	if (!var_content)
		return (ft_strdup(""));
	result = ft_strdup(var_content);
	free(var_content);
	return (result);
}
