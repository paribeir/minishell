/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bin_get_bin_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:43:25 by jdach             #+#    #+#             */
/*   Updated: 2024/07/21 10:54:59 by jdach            ###   ########.fr       */
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
	while (*paths != NULL)
	{
		path = ft_strjoin(*paths, appendix);
		cached_ptr = path;
		path = ft_strjoin(path, binary);
		free(cached_ptr);
		if (access(path, F_OK) == 0)
			return (path);
		paths++;
	}
	ft_putstr_fd("No such bin\n", 2);
	return ("");
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

char	*exe_bin_get_bin_path(t_cmd_list *cmd_list_item)
{
	char	*path;

	if (ft_strchr(cmd_list_item->binary, '/') > 0)
		path = get_binary_path_direct(cmd_list_item->binary);
	else
		path = get_binary_path_search(cmd_list_item->binary);
	return (path);
}
