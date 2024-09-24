/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:07:18 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/24 12:12:50 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*quotes_remove_one_var(char *str);

int	var_in_quote(char *str)
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
			return (in_dquote || in_squote);
		i++;
	}
	return (0);
}

void	var_in_quote_exp(char *str, int *i, int *in_squote, int *in_dquote)
{
	if (str[*i] == '\'' && !(*in_dquote))
		(*in_squote) = !(*in_squote);
	else if (str[*i] == '\"' && !(*in_squote))
		(*in_dquote) = !(*in_dquote);
	if (str[*i] == '$')
		return ;
}

char	*get_var_name(char *str, int *i)
{
	char	*dest;
	int	j;

	j = 0;
	dest = ft_calloc(ft_strlen(&str[*i]) + 1, 1);
	if (str[*i] == '$') 
		(*i)++;
	if (str[*i] == '?')
	{
		dest[j++] = str[*i];
		(*i)++;
		return (dest);
	}
	if (!str[*i] || !(ft_isalnum(str[*i]) || str[*i] == '_'))
		dest[0] = '$';
	else
	{
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		{
			dest[j++] = str[*i];
			(*i)++;
		}
	}
	return (dest);
}

char	*util_get_var(char *var, t_cmd *cmd_data)
{
	char	*exp_var;

	if (var && var[0] == '?')
		exp_var = ft_itoa(g_status);
	else if (ft_strlen(var) == 1 && var[0] == '$')
		exp_var = ft_strdup("$");
	else
		exp_var = exe_env_get_var(var, cmd_data);
	free (var);
	if (!exp_var)
		return (NULL);
	return (exp_var);
}

// This function handles variable expansion and returns the length added
int	handle_var_expansion(char *str, int *i, char *new_str, t_cmd *cmd_data)
{
	char	*var_content;
	int		len;

	len = 0;
	var_content = util_get_var(get_var_name(str, i), cmd_data);
	if (var_content)
	{
		ft_strlcat(new_str, var_content, 9999);
		len = ft_strlen(var_content);
		free(var_content);
	}
	return (len);
}

//implement flags
//while inside single quotes, copy everything
//if inside double quotes, ingnore single quotes
//as long as not inside single quotes, if ou find a dollar, get var
//when you get var, remember not to lose the rest of the string
char	*expand_vars_w_squote(char *str, t_cmd *cmd_data)
{
	int	in_squote;
	int	in_dquote;
	char	*new_str;
	int	i;
	int	j;

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
		total = (char *)ft_calloc(strlen(*current) + strlen(var) + 1, sizeof(char));
		if (total)
		{
			ft_strlcpy(total, *current, ft_strlen(*current) + ft_strlen(var) + 1);
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


//gets the variable content by name and returns it (heredoc)
char	*get_var_content(char *var_name, t_cmd *cmd_data)
{
	char	*var_content;
	char	*result;

	if (var_name[0] == '?')
	{
		result = ft_itoa(g_status);
		return (result);
	}
	var_content = exe_env_get_var(var_name, cmd_data);
	if (!var_content)
		return (ft_strdup(""));

	result = ft_strdup(var_content);
	free(var_content);

	return (result);
}



/*If '$' is followed by a '?', it will be expanded into the exit status of the last foreground process.
If there are more characters after the '?', they are kept as is, not affecting the expansion.
e.g. $?hello --> 0hello*/
// get var for heredoc
char	*get_var(char **str, t_cmd *cmd_data)
{
	char	*var_name;
	char	*var_content;

	if (!var_name)
		return (NULL);
	var_content = get_var_content(var_name, cmd_data);
	free(var_name);
	return (var_content);
}

