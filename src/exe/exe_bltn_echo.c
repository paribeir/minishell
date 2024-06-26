/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bltn_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:02:37 by jdach             #+#    #+#             */
/*   Updated: 2024/05/26 21:29:54 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_node(t_node *node, t_cmd *cmd)
{
	if ((node->flags && node->flags[1]) || (node->flags && \
	ft_strncmp(node->flags[0], "-n", ft_strlen(node->flags[0]) + 1) != 0))
		exe_err(ERR_ECHO_FLAGS, CLEANUP, cmd);
}

void	exe_bltn_echo(t_list *cmd_list_item, t_cmd *cmd)
{
	char	*str;
	t_node	*node;

	node = cmd_list_item->content;
	check_node(node, cmd);
	if (node->params == NULL)
		str = "";
	else
		str = node->params[0];
	exe_get_in_out(cmd_list_item, cmd);
	if (node->flags)
		ft_putstr_fd(str, 1);
	else
		ft_putendl_fd(str, 1);
}
