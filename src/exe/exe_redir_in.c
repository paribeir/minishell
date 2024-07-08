/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redir_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:16:55 by jdach             #+#    #+#             */
/*   Updated: 2024/05/26 23:08:26 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_redir_in(t_list *cmd_list_item, t_cmd *cmd)
{
	int		fd;
	t_node	*node;

	fd = 0;
	node = cmd_list_item->content;
	fd = open(node->params[0], O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
