/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_env_get_var_address.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:13:53 by jdach             #+#    #+#             */
/*   Updated: 2024/07/24 17:05:22 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exe_env_get_var_address(char *var, t_cmd *cmd_env)
{
	int		i;

	i = 0;
	while (cmd_env->envp[i] != NULL)
	{
		if (ft_strncmp(cmd_env->envp[i], var, ft_strlen(var)) == 0)
			return (cmd_env->envp[i]);
		i++;
	}
	return (NULL);
}
