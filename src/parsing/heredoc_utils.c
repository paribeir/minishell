/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 19:10:43 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/29 17:01:05 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_heredoc_delimiter(t_token *token, char *read_str)
{
	return ((ft_strncmp(token->next->str, read_str, \
	ft_strlen(token->next->str)) == 0 && \
	read_str[ft_strlen(token->next->str) + 1] == '\0'));
}

char	*process_heredoc_line(char *read_str, t_token *token, t_cmd *cmd_data)
{
	char	*old_read_str;

	if (ft_strchr(read_str, '$') && (token->next->subtype != SQUOTE && \
	token->next->subtype != DQUOTE))
	{
		old_read_str = read_str;
		read_str = expand_heredoc(read_str, cmd_data);
		free(old_read_str);
		if (read_str)
			read_str[ft_strlen(read_str)] = '\n';
	}
	if (!read_str)
		read_str = ft_strdup("\n");
	return (read_str);
}

int	write_heredoc_to_file(char *filename, char *final_str)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		return (-1);
	ft_putstr_fd(final_str, fd);
	close(fd);
	return (0);
}

int	handle_heredoc_delimiter(t_token *token, char *read_str, \
char *final_str, char *filename)
{
	if (!read_str || is_heredoc_delimiter(token, read_str))
	{
		free(token->next->str);
		if (write_heredoc_to_file(filename, final_str) < 0)
		{
			cleanup_memory(final_str, read_str, filename);
			return (0);
		}
		cleanup_memory(final_str, read_str, NULL);
		return (1);
	}
	return (0);
}




