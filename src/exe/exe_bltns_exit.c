/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bltns_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:14:00 by jdach             #+#    #+#             */
/*   Updated: 2024/08/24 19:47:47 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_bltns_exit(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	(void) cmd_data;
	if (cmd_list_item->arguments[0] != NULL)
		exit(ft_atoi(cmd_list_item->arguments[0]));
	exit(EXIT_SUCCESS);
}
