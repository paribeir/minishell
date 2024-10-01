/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_retry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:57:31 by paribeir          #+#    #+#             */
/*   Updated: 2024/10/01 18:30:10 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//#include <minishell.h>

/*get the name of the heredoc
char	*heredoc_filename(t_token *token)
{
	quotes_remove(&token->next);
	return (hex_to_dec(token));
}

//get the cwd. This needs to be freed
char	*heredoc_path(char *filename)
{
	char	*cwd;
	char	*heredoc_path;

	cwd = (char *)ft_calloc(1024, 1);
	cwd = getcwd(cwd, sizeof(cwd));
	if (!cwd)
		return (NULL);
	heredoc_path = ft_strjoin(cwd, filename);
	return (heredoc_path);
}

char	*heredoc_fd(char *filename)
{
	char	*fd;
	char	*here_path;

	here_path = heredoc_path(filename);
	if (!here_path)
		return (-1);
	fd = open(here_path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	free(here_path);
	return (fd);
}

int	heredoc_write_to_fd(int fd, char **final_str)
{
	int		bytes_written_1;
	int		bytes_written_2;
	char	*line;

	line = *final_str;
	bytes_written_1 = write(fd, line, ft_strlen(line));
	bytes_written_2 = write(fd, "\n", 1);
	free(line);
	*final_str = NULL;
	if (bytes_written_1 == -1 || bytes_written_2 == -1)
		return (0);
	return (1);
}
int	heredoc_to_file(char *filename, char *final_str, int fd)
{
	ft_putstr_fd(final_str, fd);
	close(fd);
	return (0);
}

int	heredoc_delimiter(t_token *token, char *read_str, \
char *final_str, char *filename, int fd)
{
	if (!read_str || is_heredoc_delimiter(token, read_str))
	{
		if (!read_str)
			ft_printf("\nminishell: warning: here-document delimited by end-of-file (wanted '%s')\n", token->next->str);
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

int	process_heredoc_loop(t_token *token, t_cmd *cmd_data, \
int fd, char *filename)
{
	char	*read_str;
	char	**final_str;

	heredoc_signals_set();
	read_str = readline(PURPLE "😈 > " NS);
	while (read_str && g_signum != SIGINT)
	{
		if (heredoc_delimiter(token, read_str, *final_str, filename, fd))
			return (exe_signals_processing(), 1);
		read_str = process_heredoc_line(read_str, token, cmd_data);
		if (!update_final_str(final_str, read_str, filename))
			return (0);
		free(read_str);
		read_str = readline(PURPLE "😈 > " NS);
		//if (g_signum == SIGINT)
			//return (exe_signals_processing(), 1);
	}
	//if (!read_str)
		//handle_heredoc_delimiter(token, read_str, *final_str, filename);
	return (exe_signals_processing(), 1);
} 

//First function that runs in case of heredoc
char	*heredoc_handler(t_token *token, t_cmd *cmd_data)
{
	char	*filename;
	int	here_fd;

	ft_putstr_fd(PURPLE "😈 > " NS, STDOUT_FILENO);
	filename = heredoc_filename(token);
	if (!filename)
		return (cleanup_memory(NULL, NULL, filename), NULL);
	here_fd = heredoc_fd(filename);
	if (here_fd < 0)
		return (cleanup_memory(NULL, NULL, filename), NULL);
	if (!process_heredoc_loop(token, cmd_data, here_fd, filename))
		return (cleanup_memory(NULL, NULL, filename), NULL);
	return (filename);
}
*/
