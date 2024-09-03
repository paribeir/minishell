/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bin_get_bin_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:43:25 by jdach             #+#    #+#             */
/*   Updated: 2024/09/03 18:10:13 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_bin_check_permission(char *path, t_cmd_list *cmd_list_item)
{
	struct stat	path_stats;

	stat(path, &path_stats);
	if (S_ISDIR(path_stats.st_mode))
	{
		exe_err_long(NULL, ERR_BIN_IS_FOLDER);
		exit(126);
	}
	else if (access(path, F_OK) == -1)
	{
		if (ft_strchr(cmd_list_item->binary, '/'))
			exe_err_long(NULL, ERR_BIN_NO_SUCH_FOLDER);
		else
			exe_err_long(NULL, ERR_BIN_NOT_FOUND);
		exit(127);
	}
	else if (access(path, X_OK) == -1)
	{
		exe_err_long(NULL, ERR_BIN_NON_EXECUTABEL);
		exit(126);
	}
}

char	*exe_bin_get_bin_path_search(char *binary, t_cmd *cmd_data)
{
	char	*paths_str;
	char	**paths_arr;
	char	*cached_ptr;
	char	*path;
	int		i;

	paths_str = exe_env_get_var("PATH", cmd_data);
	if (paths_str == NULL)
		exe_err_long(binary, ERR_BIN_NO_SUCH_FOLDER);
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
	return (exe_cleanup_strarray(paths_arr), free(paths_str), NULL);
}

char	*exe_bin_get_bin_path(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	char	*path;

	if (ft_strchr(cmd_list_item->binary, '/'))
		path = ft_strdup(cmd_list_item->binary);
	else
		path = exe_bin_get_bin_path_search(cmd_list_item->binary, cmd_data);
	exe_bin_check_permission(path, cmd_list_item);
	return (path);
}
