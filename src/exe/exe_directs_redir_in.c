/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_directs_redir_in.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:16:55 by jdach             #+#    #+#             */
/*   Updated: 2024/08/26 19:16:47 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_directs_redir_in(t_cmd_list *cmd_list_item)
{
	int		fd;

	fd = open(cmd_list_item->arguments[0], O_RDONLY);
	if (fd == -1)
	{
		exe_err_long(ERR_NO_SUCH_FILE);
		g_status = 1;
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}
