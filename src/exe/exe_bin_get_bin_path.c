/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bin_get_bin_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:43:25 by jdach             #+#    #+#             */
/*   Updated: 2024/08/29 13:11:58 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exe_bin_get_bin_path_search(char *binary, t_cmd *cmd_data)
{
	char	*paths_str;
	char	**paths_arr;
	char	*cached_ptr;
	char	*path;
	int		i;

	paths_str = exe_env_get_var("PATH", cmd_data);
	paths_arr = ft_split(paths_str, ':');
	i = -1;
	while (paths_arr[++i] != NULL)
	{
		path = ft_strjoin(paths_arr[i], "/");
		cached_ptr = path;
		path = ft_strjoin(path, binary);
		free(cached_ptr);
		if (access(path, F_OK) == 0)
			return (exe_cleanup_strarray(paths_arr), free(paths_str), path);
		free(path);
	}
	exe_err_long(ERR_BIN_NOT_FOUND);
	return (exe_cleanup_strarray(paths_arr), free(paths_str), NULL);
}

char	*exe_bin_get_bin_path_direct(char *binary)
{
	if (access(binary, F_OK) == 0)
		return (ft_strdup(binary));
	exe_err_long(ERR_FD_NO_SUCH_FILE);
	return (NULL);
}

char	*exe_bin_get_bin_path(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	char	*path;

	if (ft_strchr(cmd_list_item->binary, '/'))
		path = exe_bin_get_bin_path_direct(cmd_list_item->binary);
	else
		path = exe_bin_get_bin_path_search(cmd_list_item->binary, cmd_data);
	return (path);
}
