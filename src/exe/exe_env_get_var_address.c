/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_env_get_var_address.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:13:53 by jdach             #+#    #+#             */
/*   Updated: 2024/09/27 10:23:41 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exe_env_get_var_address(char *var, t_cmd *cmd_data)
{
	int		i;
	char	**env_var;

	i = 0;
	while (cmd_data->envp[i] != NULL)
	{
		env_var = ft_split(cmd_data->envp[i], '=');
		if (ft_strncmp(var, env_var[0], ft_strlen(var) + 1) == 0)
		{
			exe_cleanup_strarray(env_var);
			return (cmd_data->envp[i]);
		}
		i++;
	}
	return (NULL);
}
