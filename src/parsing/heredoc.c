/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patricia <patricia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:49:00 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/01 12:47:19 by patricia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//--> TO-DO: Add return value if gnl fails
//eval if we need a check before quote removal
//Does this work with more than one heredoc?
char	*heredoc_handler(t_token *token, t_cmd *cmd_data)
{
	char	*read_str;
	char	*final_str;
	char	*temp_str;
	int		fd;
	char	*filename;

	ft_putstr_fd(">>> ", STDOUT_FILENO);
	final_str = ft_strdup("");
	read_str = ft_get_next_line(0);
	quotes_remove(&token->next);
	filename = hex_to_dec(token);
	while (read_str)
	{
		if (ft_strncmp(token->next->str, read_str, \
		ft_strlen(token->next->str)) == 0 && \
		read_str[ft_strlen(token->next->str) + 1] == '\0')
		{
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666); //this one here
			ft_putstr_fd(final_str, fd);
			free(final_str);
			free(read_str);
			close(fd);
			return (filename);
		}
		else if (ft_strchr(read_str, '$') && (token->next->subtype != SQUOTE && token->next->subtype != DQUOTE))
        	{
			read_str = expand_heredoc(read_str, cmd_data);
			if (read_str)
				read_str[ft_strlen(read_str)] = '\n';
		}
		if (!read_str)
			read_str = "\n";
		temp_str = ft_strjoin(final_str, read_str);
		free(final_str);
		final_str = temp_str;
		free(read_str);
		ft_putstr_fd(">>> ", STDOUT_FILENO);
		read_str = ft_get_next_line(0);
		}
	free(final_str);
	return (NULL);
}

//expanding env vars knowing there are no single quotes
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
		dollar = next_dollar;
	}
	return (sum);
}

char *aux_str_join(char *str1, char *str2)
{
	char *temp;

	temp = ft_strjoin(str1, str2);

	if (str1)
		free(str1);
	return (temp);
}
