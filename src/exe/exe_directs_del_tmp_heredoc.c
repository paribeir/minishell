/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_directs_del_tmp_heredoc.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:37:18 by jdach             #+#    #+#             */
/*   Updated: 2024/09/29 21:45:50 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_directs_del_tmp_heredoc(t_cmd_list *cmd_list_item)
{
	while (cmd_list_item && cmd_list_item->type != T_PIPE)
	{
		if (cmd_list_item->type == HEREDOC)
			unlink(cmd_list_item->arguments[0]);
		cmd_list_item = cmd_list_item->next;
	}
}
