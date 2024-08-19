/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cleanup_aftercmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:19:21 by jdach             #+#    #+#             */
/*   Updated: 2024/08/18 14:29:46 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_cleanup_aftercmd(t_cmd_list *cmd_list)
{
	t_cmd_list	*tmp_ptr;

	while (cmd_list)
	{
		tmp_ptr = cmd_list->next;
		free(cmd_list->binary);
		exe_cleanup_strarray(cmd_list->arguments);
		free(cmd_list);
		cmd_list = tmp_ptr;
	}
}
