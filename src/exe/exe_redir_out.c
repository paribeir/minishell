/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redir_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:16:55 by jdach             #+#    #+#             */
/*   Updated: 2024/05/26 22:19:44 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_redir_out(t_list *cmd_list_item, t_cmd *cmd)
{
	int		fd;
	t_node	*node;

	fd = 1;
	node = cmd_list_item->content;
	fd = open(node->params[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
