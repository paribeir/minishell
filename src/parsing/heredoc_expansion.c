/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:29:42 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/27 18:52:05 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*aux_str_join(char *str1, char *str2)
{
	char	*temp;

	if (!str1)
		return (ft_strdup(str2));
	if (!str2)
		return (str1);
	temp = ft_strjoin(str1, str2);
	if (!temp)
		return (NULL);
	free(str1);
	return (temp);
}

//expanding env vars ignoring single quotes
char	*expand_heredoc(char *str, t_cmd *cmd_data)
{
	char	*sum;
	char	*before_var;
	char	*dollar;
	char	*var_value;
	char	*next_dollar;

	sum = ft_strdup("");
	dollar = str;
	while (dollar && *dollar)
	{
		next_dollar = ft_strchr(dollar, '$');
		if (!next_dollar)
		{
			sum = aux_str_join(sum, dollar);
			break ;
		}
		before_var = ft_substr(dollar, 0, next_dollar - dollar);
		sum = aux_str_join(sum, before_var);
		var_value = get_var(&next_dollar, cmd_data);
		sum = aux_str_join(sum, var_value);
		free(var_value);
		free(before_var);
		dollar = next_dollar;
	}
	return (sum);
}
