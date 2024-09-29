/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:27:29 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/29 17:15:55 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_print_cmds(t_cmd_list *cmd, int active)
{
	int			i;

	while (active != 0 && cmd)
	{
		i = -1;
		ft_printf("Type: %d\n", cmd->type);
		if (cmd->binary)
			ft_printf("	Binary: %s\n", cmd->binary);
		if (cmd->type != T_PIPE && cmd->type != AND_IF && cmd->type != OR_IF)
			while (cmd->arguments && cmd->arguments[++i])
				ft_printf("	Argument %d: %s\n", i, cmd->arguments[i]);
		cmd = cmd->next;
	}
}
