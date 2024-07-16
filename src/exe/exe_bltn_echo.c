/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bltn_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:02:37 by jdach             #+#    #+#             */
/*   Updated: 2024/07/16 22:24:35 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_bltn_echo(t_cmd_list *cmd_list_item, t_cmd *cmd)
{
	if ((cmd_list_item->arguments && cmd_list_item->arguments[1]) || (cmd_list_item->arguments && \
	ft_strncmp(cmd_list_item->arguments[0], "-n", ft_strlen(cmd_list_item->arguments[0]) + 1) != 0))
		exe_err(ERR_ECHO_FLAGS, CLEANUP, cmd);
}

void	exe_bltn_echo(t_cmd_list *cmd_list_item, t_cmd *cmd)
{
	char	*str;

	check_bltn_echo(cmd_list_item, cmd);
	if (cmd_list_item->arguments == NULL)
		str = "";
	else
		str = cmd_list_item->arguments[0];
	exe_get_in_out(cmd_list_item, cmd);
	if (cmd_list_item->arguments)
		ft_putstr_fd(str, 1);
	else
		ft_putendl_fd(str, 1);
}
