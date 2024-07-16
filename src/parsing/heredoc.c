/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:49:00 by paribeir          #+#    #+#             */
/*   Updated: 2024/07/16 16:58:52 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "parser.h"

//--> TO-DO: Add return value if gnl fails
//eval if we need a check before quote removal
//Does this work with more than one heredoc?
char	*heredoc_handler(t_token *token)
{
	char	*read_str;
	char	*final_str;
	char	*temp_str;
	int		fd;

	ft_putstr_fd(">>> ", STDOUT_FILENO);
	final_str = ft_strdup("");
	read_str = ft_get_next_line(0);
    	quotes_remove(&token->next);
	while (read_str)
	{
		if (ft_strncmp(token->next->str, read_str, \
		ft_strlen(token->next->str)) == 0 && \
		read_str[ft_strlen(token->next->str) + 1] == '\0')
		{
			fd = open("here_doc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
			ft_putstr_fd(final_str, fd);
			free(final_str);
			free(read_str);
			close(fd);
			return ("here_doc_temp");
		}
		else if (ft_strchr(read_str, '$') && (token->next->subtype != SQUOTE && token->next->subtype != DQUOTE))
        	{
			read_str = expand_heredoc(read_str);
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
char	*expand_heredoc(char *str)
{
	char	*sum;
	char	*before_var;
	char	*dollar;

	sum = ft_strdup("");
	dollar = str;
	while (dollar)
	{
		dollar = ft_strchr(str, '$');
		if (!dollar)
		{
			sum = aux_str_join(sum, str);
			break ;
		}
		else
		{
			before_var = ft_substr(str, 0, ft_strchr(str, '$') - str);
			sum = aux_str_join(sum, before_var);
			sum = aux_str_join(sum, get_var(&dollar));
		}
		dollar = ft_strchr(dollar, '$');
		if (dollar)
			dollar++;
	}
	return (sum);
}

char *aux_str_join(char *str1, char *str2)
{
	char *temp;

	temp = ft_strjoin(str1, str2);

	if (str1)
		free(str1);
	//if (str2)
	//	free(str2);
	return (temp);
}
