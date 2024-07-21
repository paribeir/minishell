/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_directs_redir_out.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:06:19 by jdach             #+#    #+#             */
/*   Updated: 2024/07/21 11:48:31 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_directs_redir_out(t_cmd_list *cmd_list_item)
{
	int	fd;

	fd = open(cmd_list_item->arguments[0], \
	O_WRONLY | O_CREAT | O_TRUNC, 0666);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}