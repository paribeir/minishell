/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_env_set_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:13:53 by jdach             #+#    #+#             */
/*   Updated: 2024/07/24 17:37:56 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_env_set_var(char *var, char *value, t_cmd *cmd_env)
{
	int		i;
	char	*str_val;
	char	*temp_ptr;

	i = 0;
	str_val = var;
	while (cmd_env->envp[i] != NULL)
	{
		if (ft_strncmp(cmd_env->envp[i], var, ft_strlen(var)) == 0)
		{
			str_val = ft_strjoin(str_val, "=");
			temp_ptr = str_val;
			str_val = ft_strjoin(str_val, value);
			free(temp_ptr);
			free(cmd_env->envp[i]);
			cmd_env->envp[i] = str_val;
		}
		i++;
	}
}
