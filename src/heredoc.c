/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:49:00 by paribeir          #+#    #+#             */
/*   Updated: 2024/07/04 22:23:53 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/tokenizer.h"
#include "../inc/parser.h"

//--> TO-DO: Add return value if gnl fails
//eval if we need a check before quote removal
char	*heredoc_handler(t_token *token)
{
	char	*read_str;
	char	*final_str;
	int		fd;

	final_str = ft_strdup("");
	read_str = ft_get_next_line(0);
    quotes_remove(token->next);
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
}
