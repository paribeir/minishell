/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_directs_append.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:16:55 by jdach             #+#    #+#             */
/*   Updated: 2024/07/21 16:32:54 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_directs_append(t_cmd_list *cmd_list_item)
{
	int		fd;

	fd = 0;
	fd = open(cmd_list_item->arguments[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
