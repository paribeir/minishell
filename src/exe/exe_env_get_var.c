/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_env_get_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:13:53 by jdach             #+#    #+#             */
/*   Updated: 2024/07/24 17:10:23 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exe_env_get_var(char *var, t_cmd *cmd_env)
{
	char	*env_var_string;
	char	**split_strings;

	env_var_string = exe_env_get_var_address(var, cmd_env);
	if (env_var_string)
	{
		split_strings = ft_split(env_var_string, '=');
		return (split_strings[1]);
	}
	return (NULL);
}
