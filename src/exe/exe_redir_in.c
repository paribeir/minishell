/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redir_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:16:55 by jdach             #+#    #+#             */
/*   Updated: 2024/07/16 22:41:16 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_redir_in(t_cmd_list *cmd_list_item, t_cmd *cmd)
{
	int		fd;

	fd = open(cmd_list_item->arguments[0], O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
