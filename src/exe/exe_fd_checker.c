/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_fd_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 01:10:21 by jdach             #+#    #+#             */
/*   Updated: 2024/09/02 16:35:46 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_fd_checker_in_append(t_cmd_list *cmd_list_item, int *err_printing)
{
	char	*file_path;

	file_path = cmd_list_item->arguments[0];
	if (access(file_path, F_OK) != 0 && *err_printing == 1)
	{
		exe_err_long(ERR_FD_NO_SUCH_FILE);
		*err_printing = 0;
	}
	if (access(file_path, R_OK) != 0 && *err_printing == 1)
	{
		exe_err_long(ERR_FD_NOT_READABLE);
		*err_printing = 0;
	}
}

char	*exe_fd_checker_extract_folder(char *path)
{
	char	*folder_path;
	int		i;
	int		end_of_folder;

	folder_path = 0;
	i = 0;
	end_of_folder = 0;
	while (path[i] != '\0')
	{
		if (path[i] == '/')
			end_of_folder = i;
		i++;
	}
	folder_path = ft_calloc(end_of_folder + 1, sizeof(char));
	ft_strlcpy(folder_path, path, end_of_folder + 1);
	return (folder_path);
}

void	exe_fd_checker_redir_out(t_cmd_list *cmd_list_item, int *err_printing)
{
	char	*file_path;

	file_path = cmd_list_item->arguments[0];
	if (ft_strchr(file_path, '/'))
	{
		if (access(exe_fd_checker_extract_folder(file_path), F_OK) != 0)
		{
			exe_err_long(ERR_BIN_NO_SUCH_FOLDER);
			*err_printing = 0;
		}
	}
	if (access(file_path, F_OK) == 0 && \
	access(file_path, W_OK) != 0 && *err_printing == 1)
	{
		exe_err_long(ERR_FD_NOT_WRITABLE);
		*err_printing = 0;
	}
}

void	exe_fd_checker(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	int				err_printing;
	t_token_subtype	type;

	err_printing = 1;
	while (cmd_list_item)
	{
		type = cmd_list_item->type;
		if (type == REDIR_IN || type == REDIR_APPEND)
			exe_fd_checker_in_append(cmd_list_item, &err_printing);
		else if (type == REDIR_OUT)
			exe_fd_checker_redir_out(cmd_list_item, &err_printing);
		else if (type == T_PIPE)
			err_printing = 1;
		cmd_list_item = cmd_list_item->next;
	}
	(void)cmd_data;
}
