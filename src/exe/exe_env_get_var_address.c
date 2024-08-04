/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_env_get_var_address.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:13:53 by jdach             #+#    #+#             */
/*   Updated: 2024/08/04 10:07:42 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exe_env_get_var_address(char *var, t_cmd *cmd_data)
{
	int		i;

	i = 0;
	while (cmd_data->envp[i] != NULL)
	{
		if (ft_strncmp(cmd_data->envp[i], var, ft_strlen(var)) == 0)
			return (cmd_data->envp[i]);
		i++;
	}
	return (NULL);
}
