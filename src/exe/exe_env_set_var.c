/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_env_set_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:13:53 by jdach             #+#    #+#             */
/*   Updated: 2024/08/04 10:07:41 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_env_set_var_override(char *var_str, char **cmd_env_str)
{
	free(*cmd_env_str);
	*cmd_env_str = var_str;
	return (0);
}

int	exe_env_set_var_new(char *var_str, t_cmd *cmd_data)
{
	int		i;
	int		arr_size;
	char	**new_env_array;

	arr_size = 0;
	while (cmd_data->envp[arr_size])
		arr_size++;
	new_env_array = malloc(sizeof(char *) * arr_size + 2);
	i = -1;
	while (++i < arr_size)
	{
		new_env_array[i] = ft_strdup(cmd_data->envp[i]);
		free(cmd_data->envp[i]);
	}
	free(cmd_data->envp);
	new_env_array[i++] = var_str;
	new_env_array[i++] = NULL;
	cmd_data->envp = new_env_array;
	return (0);
}

char	*exe_env_set_var_get_var_str(char *var, char *value)
{
	char	*var_str;
	char	*temp_ptr;

	var_str = var;
	var_str = ft_strjoin(var_str, "=");
	temp_ptr = var_str;
	var_str = ft_strjoin(var_str, value);
	free(temp_ptr);
	return (var_str);
}

int	exe_env_set_var(char *var, char *value, t_cmd *cmd_data)
{
	int		i;
	char	*var_str;

	i = -1;
	var_str = exe_env_set_var_get_var_str(var, value);
	while (cmd_data->envp[++i] != NULL)
		if (ft_strncmp(cmd_data->envp[i], var, ft_strlen(var)) == 0)
			return (exe_env_set_var_override(var_str, &cmd_data->envp[i]), 0);
	return (exe_env_set_var_new(var_str, cmd_data), 0);
}
