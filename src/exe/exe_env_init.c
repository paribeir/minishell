/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_env_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:32:14 by jdach             #+#    #+#             */
/*   Updated: 2024/07/26 16:10:01 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_env_init(t_cmd *cmd_env, char *envp[])
{
	int		lines_n;
	int		i;
	char	**env_array;

	lines_n = 0;
	i = -1;
	while (envp[lines_n])
		lines_n++;
	env_array = malloc(sizeof(char *) * (lines_n + 1));
	while (envp[++i])
		env_array[i] = ft_strdup(envp[i]);
	env_array[i] = NULL;
	cmd_env->envp = env_array;
}
