/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 01:10:21 by jdach             #+#    #+#             */
/*   Updated: 2024/05/26 23:01:06 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_binary_path_search(char *binary)
{
	char	*appendix;
	char	**paths;
	char	*cached_ptr;
	char	*path;

	appendix = "/";
	paths = ft_split(getenv("PATH"), ':');
	while (paths)
	{
		path = ft_strjoin(*paths, appendix);
		cached_ptr = path;
		path = ft_strjoin(path, binary);
		free(cached_ptr);
		if (access(path, F_OK) == 0)
			return (path);
		paths++;
	}
	ft_putstr_fd("No such bin", 2);
	exit (1);
}

char	*get_binary_path_direct(char *binary)
{
	if (access(binary, F_OK) == 0)
		return (binary);
	else
	{
		ft_putstr_fd("No such bin", 2);
		exit (1);
	}
}


void	exe_bin(t_list *cmd_list_item, t_cmd *cmd)
{
	char	*path;
	int		pid;
	t_node	*node;

	node = cmd_list_item->content;
	exe_look_ahead(cmd_list_item, cmd);
	if (ft_strchr(node->binary, '/') > 0)
		path = get_binary_path_direct(node->binary);
	else
		path = get_binary_path_search(node->binary);
	pid = fork();
	if (pid == 0)
		execve(path, node->params, NULL);
}
