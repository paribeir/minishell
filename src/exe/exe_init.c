/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:32:14 by jdach             #+#    #+#             */
/*   Updated: 2024/07/24 15:54:03 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_init(t_cmd *cmd_env, char *envp[])
{
	int	lines_n;
	int	i;

	lines_n = 0;
	i = -1;
	while (envp[lines_n])
		lines_n++;
	cmd_env->envp = malloc(sizeof(char *) * (lines_n + 1));
	while (envp[++i])
		cmd_env->envp[i] = ft_strdup(envp[i]);
	cmd_env->envp[i] = NULL;
}
