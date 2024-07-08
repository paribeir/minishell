/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_here_doc_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:37:18 by jdach             #+#    #+#             */
/*   Updated: 2024/05/26 22:17:34 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_here_doc_fd(t_node *node, t_cmd *cmd, char	*dlmtr)
{
	char	*current_str;
	char	*final_str;
	int		fd;

	final_str = "";
	current_str = ft_get_next_line(0);
	while (current_str)
	{
		if (ft_strncmp(dlmtr, current_str, ft_strlen(dlmtr)) == 0 && \
		current_str[ft_strlen(dlmtr) + 1] == '\0')
		{
			fd = open("temp_file", O_WRONLY | O_CREAT | O_TRUNC, 0666);
			ft_putstr_fd(final_str, fd);
			free(final_str);
			free(current_str);
			close(fd);
			fd = open("temp_file", O_RDONLY);
			return (fd);
		}
		final_str = ft_strjoin(final_str, current_str);
		free (current_str);
		current_str = ft_get_next_line(0);
	}
	return (-1);
}

void	exe_here_doc(t_list *cmd_list_item, t_cmd *cmd)
{
	int		fd;
	t_node	*node;

	fd = 0;
	node = cmd_list_item->content;
	fd = exe_here_doc_fd(node, cmd, node->params[0]);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
