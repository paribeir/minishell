/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:07:18 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/24 10:58:30 by paribeir         ###   ########.fr       */
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
	char	*var_content;

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
		{
			var_content = util_get_var(get_var_name(str, &i), cmd_data);
			if (var_content)
			{
				ft_strlcat(new_str, var_content, 9999);
				j += ft_strlen(var_content);
				free (var_content);
			}
		}
	}
	return (new_str);
}

/*char	*expand_vars_w_squote(char *str, t_cmd *cmd_data)
{
	char	*dollar;
	char	*before_var;
	char	*var_value;
	char	*sum;
	char	*var_no_quotes;

	dollar = str;
	sum = ft_strdup("");
	while (dollar && *dollar)
	{
		if (var_in_quote(dollar))
		{
			before_var = ft_substr(dollar, 0, ft_strchr(dollar, '$') - dollar - 1);
			if (!var_in_squote(dollar))
				var_no_quotes = quotes_remove_one_var(dollar);
		}
		else
			before_var = ft_substr(dollar, 0, ft_strchr(dollar, '$') - dollar);
		dollar = dollar + ft_strlen(before_var);
		sum = aux_str_join(sum, before_var);
		if (*dollar && !var_in_squote(dollar))
		{
			if (var_in_quote(dollar))
			{
				var_value = get_var(&var_no_quotes, cmd_data);
				//free(var_no_quotes);
				dollar = ft_strchr((ft_strchr(dollar, '\"') + 1), '\"') + 1;
			}
			else
				var_value = get_var(&dollar, cmd_data);
		}
		else
			var_value = add_literal(&dollar);
		sum = aux_str_join(sum, var_value);
		free(var_value);
		free(before_var);
	}
	return (sum);
}*/


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
//fix this BS logic
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
		//free (var);
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

/*If '$' is followed by a '?', it will be expanded into the exit status of the last foreground process.
If there are more characters after the '?', they are kept as is, not affecting the expansion.
e.g. $?hello --> 0hello*/
char	*get_var(char **str, t_cmd *cmd_data)
{
	char	*var_name;
	char	*start;
	char	*var_content;
	char	*result;

	while (**str && **str != '$')
		(*str)++;
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
