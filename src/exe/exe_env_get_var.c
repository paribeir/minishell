/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_env_get_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patricia <patricia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:13:53 by jdach             #+#    #+#             */
/*   Updated: 2024/08/31 14:47:33 by patricia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//P: function added to check if there is something after the '=' sign
int	env_check_empty(char *env_var_string)
{
	char	*str;

	str = ft_strchr(env_var_string, '=');
	if (str && str[1])
		return (1);
	return (0);
}

char	*exe_env_get_var(char *var, t_cmd *cmd_data)
{
	char	*env_var_string;
	char	*return_str;
	char	**split_strings;

	env_var_string = exe_env_get_var_address(var, cmd_data);
	if (env_var_string && env_check_empty(env_var_string))
	{
		split_strings = ft_split(env_var_string, '=');
		return_str = ft_strdup(split_strings[1]);
		exe_cleanup_strarray(split_strings);
		return (return_str);
	}
	return (NULL);
}
