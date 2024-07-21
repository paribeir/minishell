/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_directs_here_doc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:37:18 by jdach             #+#    #+#             */
/*   Updated: 2024/07/21 16:46:55 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_directs_here_doc(t_cmd_list *cmd_list_item)
{
	int	fd;

	fd = open(cmd_list_item->arguments[0], O_RDONLY);
	unlink(cmd_list_item->arguments[0]);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
