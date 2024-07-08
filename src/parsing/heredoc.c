/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:49:00 by paribeir          #+#    #+#             */
/*   Updated: 2024/07/08 23:47:54 by paribeir         ###   ########.fr       */
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
	int		fd;

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
		ft_strjoin(final_str, read_str);
		free(read_str);
		read_str = ft_get_next_line(0);
		if (token->next->subtype != SQUOTE || token->next->subtype != DQUOTE)
            read_str = expand_heredoc(read_str);
	}
	return (NULL);
}

//expanding env vars knowing there are no single quotes
char	*expand_heredoc(char *str)
{
	char	*sum;
	char	*before_var;

	sum = ft_strdup("");
	while (*str)
	{
		if (!ft_strchr(str, '$'))
		{
			sum = aux_str_join(sum, str);
			break ;
		}
		else
		{
			before_var = ft_substr(str, 0, ft_strchr(str, '$') - str);
			sum = aux_str_join(sum, before_var);
			sum = aux_str_join(sum, get_var(&str));
		}
		str = ft_strchr(str, '$') + 1;
	}
	return (sum);
}

char *aux_str_join(char *str1, char *str2)
{
	char *temp;

	temp = ft_strjoin(str1, str2);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (temp);
}