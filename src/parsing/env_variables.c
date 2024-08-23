/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:07:18 by paribeir          #+#    #+#             */
/*   Updated: 2024/08/23 17:30:34 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check mem management
void	expand_env_vars(t_token	*token, t_cmd *cmd_data)
{
	char *str;
	char *current;

	if (!ft_strchr(token->str, '\''))
		token->str = expand_heredoc(token->str, cmd_data);
	else
	{
		current = ft_strdup("");
		str = token->str;
		while (*str)
		{
			if (ft_strchr(str, '$') && !var_in_squote(str))
				add_expanded_var(&current, &str, cmd_data); //expand this var
			else
				add_literal(&current, &str); //copy everything inside single quotes
		}
		free(token->str);
		token->str = current; //overwrite token->str with new string. Do I need to alloc more memory?
	}
}

void	add_expanded_var(char **current, char **str, t_cmd *cmd_data)
{
	char	*var;
	char	*total;

	var = get_var(str, cmd_data); //TO DO: check if this advances the string past the var name
	if (*var)
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

	(*str)++;
	start = *str;
	if (start && start[0] == '?')
	{
		(*str)++;
		return (ft_strdup(ft_itoa(cmd_data->exit_status)));
	}
	else if (!start || (!ft_isalnum(*start) && *start != '_'))
		return ("$");
	while (**str && (ft_isalnum(**str) || **str == '_'))
		(*str)++;
	var_name = ft_substr(start, 0, *str - start);
	if (!var_name)
		return (NULL);
	var_content = exe_env_get_var(var_name, cmd_data);
	free(var_name);
	if (!var_content)
		return (ft_strdup(""));
	return (ft_strdup(var_content)); 
}

/*return (ft_strdup(ft_itoa(cmd_data->exit_status)));
char	*expand_error_code(char *str, t_cmd *cmd_data)
{
	char	*error_code;
	char	*complete_str;
	char	*other;


	error_code = ft_strdup(ft_itoa(cmd_data->exit_status));
	if (!error_code)
		reutrn (NULL);
	if (!(++str))
		return (error_code);
	if (str[0] == '$') //what if its followed by more variables? e.g. "$?$?$?"
		//fill
	complete_str = (char*)ft_calloc(ft_strlen(error_code) + ft_strlen(*str) + 1, 1);
	if (!complete_str)
		return (NULL);
	complete_str = ft_strjoin(error_code, *str);
	return (complete_str);
}*/
/*
char	*get_var(char **str, t_cmd *cmd_data)
{
	char	*var;
	char	*start;
	char	*var_content;
	char	*error_code;
	char	*complete_str;

	complete_str = "";
	error_code = ft_strdup(ft_itoa(cmd_data->exit_status));
	if (!error_code)
		return (NULL);
	while (**str)
	{
		while (**str && **str != '$')
		if (**str == '?')
			complete_str = ft_strjoin(complete_str, error_code);
		else if (**str && (ft_isalnum(**str) || **str == '_'))
			complete_str = ft_strjoin(complete_str, expand_regular_var(str, cmd_data));
		else
			(*str)++;

	}
	(*str)++;
	start = *str;
	if (start && start[0] == '?')
		return (ft_strdup(ft_itoa(cmd_data->exit_status)));
	else if (!start || (!ft_isalnum(*start) && *start != '_'))
		return ("$");
	while (**str && (ft_isalnum(**str) || **str == '_'))
		(*str)++;
	var_name = ft_substr(start, 0, *str - start);
	if (!var_name)
		return (NULL);
	var_content = exe_env_get_var(var_name, cmd_data);
	free(var_name);
	if (!var_content)
		return (ft_strdup(""));
	return (ft_strdup(var_content)); 
}




$
next
is it a ?
expand
else
is is 
does it have anything afterwards?
is it a $?
next
is it a ?
expand
....
is it */
