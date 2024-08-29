/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bltns_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:14:00 by jdach             #+#    #+#             */
/*   Updated: 2024/08/29 19:43:21 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_bltns_exit(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	int		i;
	char	*str;

	i = -1;
	(void) cmd_data;
	str = cmd_list_item->arguments[0];
	if (cmd_list_item->arguments[0] && cmd_list_item->arguments[1])
	{
		exe_err_long(ERR_TOO_MANY_ARGS);
		exit(1);
	}
	if (str != NULL)
	{
		while (str[++i] != '\0')
		{
			if ((str[i] < 48 || str[i] > 57) && (str[i] != 45 && str[i] != 43))
			{
				exe_err_long(ERR_EXIT_NO_NBR);
				exit(2);
			}
		}
		exit(ft_atoi(cmd_list_item->arguments[0]));
	}
	exit(EXIT_SUCCESS);
}
