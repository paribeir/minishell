/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:07:18 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/27 18:50:53 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*quotes_remove_one_var(char *str);

void	var_in_quote_exp(char *str, int *i, int *in_squote, int *in_dquote)
{
	if (str[*i] == '\'' && !(*in_dquote))
		(*in_squote) = !(*in_squote);
	else if (str[*i] == '\"' && !(*in_squote))
		(*in_dquote) = !(*in_dquote);
	if (str[*i] == '$')
		return ;
}

int	var_in_quote(char *str)
{
	int	i;
	int	in_squote;
	int	in_dquote;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
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

char	*get_var_name(char *str, int *i)
{
	char	*dest;
	int		j;

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
