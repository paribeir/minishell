/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bltns_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:20:32 by jdach             #+#    #+#             */
/*   Updated: 2024/08/30 08:47:30 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_bltns_unset_recreate(char *var, t_cmd *cmd_data)
{
	int		i;
	int		j;
	char	**env_array;
	int		lines_n;

	lines_n = 0;
	while (cmd_data->envp[lines_n])
		lines_n++;
	env_array = malloc(sizeof(char *) * (lines_n));
	i = -1;
	j = 0;
	while (cmd_data->envp[++i])
	{
		if (ft_strncmp(var, cmd_data->envp[i], ft_strlen(var)) == 0 \
		&& cmd_data->envp[i][ft_strlen(var)] == '=')
			;
		else
			env_array[j++] = ft_strdup(cmd_data->envp[i]);
	}
	env_array[j] = NULL;
	exe_cleanup_strarray(cmd_data->envp);
	cmd_data->envp = env_array;
}

void	exe_bltns_unset_search(char *var, t_cmd *cmd_data)
{
	int		i;

	i = -1;
	while (cmd_data->envp[++i])
		if (ft_strncmp(var, cmd_data->envp[i], ft_strlen(var)) == 0 && \
		cmd_data->envp[i][ft_strlen(var)] == '=')
			exe_bltns_unset_recreate(var, cmd_data);
}

void	exe_bltns_unset(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	int		j;
	char	*var;

	g_status = 0;
	j = -1;
	while (cmd_list_item->arguments[++j])
	{
		var = cmd_list_item->arguments[j];
		exe_bltns_unset_search(var, cmd_data);
	}
}
