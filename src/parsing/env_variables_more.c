/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables_more.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:42:39 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/29 15:49:41 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//implement flags
//while inside single quotes, copy everything
//if inside double quotes, ingnore single quotes
//as long as not inside single quotes, if ou find a dollar, get var
//when you get var, remember not to lose the rest of the string
char	*expand_vars_w_squote(char *str, t_cmd *cmd_data)
{
	char	*new_str;
	int		in_squote;
	int		in_dquote;
	int		i;
	int		j;

	in_squote = 0;
	in_dquote = 0;
	i = 0;
	j = 0;
	new_str = (char *)ft_calloc(9999, 1);
	while (str && str[i])
	{
		var_in_quote_exp(str, &i, &in_squote, &in_dquote);
		if (in_squote || str[i] != '$')
			new_str[j++] = str[i++];
		else
			j += handle_var_expansion(str, &i, new_str, cmd_data);
	}
	return (new_str);
}

char	*find_dollar(char *str)
{
	char	*dollar;

	dollar = ft_strdup("");
	if (!var_in_squote(str))
		dollar = ft_strchr(str, '$');
	else if (ft_strchr(str, '$'))
		dollar = ft_strchr(str - 1, '$');
	else
		dollar = NULL;
	return (dollar);
}

void	expand_env_vars(t_token	*token, t_cmd *cmd_data)
{
	char	*sum;

	sum = expand_vars_w_squote(token->str, cmd_data);
	free(token->str);
	token->str = sum;
}

void	add_expanded_var(char **current, char **str, t_cmd *cmd_data)
{
	char	*var;
	char	*total;

	var = get_var(str, cmd_data);
	if (var)
	{
		total = (char *)ft_calloc(strlen(*current) + \
		strlen(var) + 1, sizeof(char));
		if (total)
		{
			ft_strlcpy(total, *current, ft_strlen(*current) + \
			ft_strlen(var) + 1);
			ft_strlcat(total, var, ft_strlen(*current) + ft_strlen(var) + 1);
			free (*current);
			*current = total;
		}
	}
}

//make function usable for wildcard as well?
char	*add_literal(char **str)
{
	char	*total;
	char	*sum;
	int		i;

	sum = ft_strdup("");
	total = (char *)ft_calloc(ft_strlen(*str), 1);
	i = 0;
	while (**str && **str != '$')
		(*str)++;
	while (**str && **str != '\'')
	{
		total[i++] = **str;
		(*str)++;
	}
	total[i] = '\0';
	if (ft_strchr(total, '$') && (**str) == '\'')
	{
		total[i++] = **str;
		(*str)++;
	}
	total[i] = '\0';
	sum = aux_str_join(sum, total);
	free(total);
	return (sum);
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
