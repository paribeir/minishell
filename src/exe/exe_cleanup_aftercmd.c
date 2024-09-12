/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cleanup_aftercmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:19:21 by jdach             #+#    #+#             */
/*   Updated: 2024/09/12 16:10:05 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst_exit_codes_content(void *content)
{
	t_exit_status	*typed_content;

	typed_content = content;
	free(typed_content);
}

void	exe_cleanup_aftercmd(t_cmd_list *cmd_list, t_cmd *cmd_data)
{
	t_cmd_list	*tmp_ptr;

	while (cmd_list)
	{
		ft_lstclear(&cmd_data->exit_codes, free_lst_exit_codes_content);
		tmp_ptr = cmd_list->next;
		free(cmd_list->binary);
		exe_cleanup_strarray(cmd_list->arguments);
		free(cmd_list);
		cmd_list = tmp_ptr;
	}
}
