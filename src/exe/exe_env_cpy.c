/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_env_cpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:32:14 by jdach             #+#    #+#             */
/*   Updated: 2024/08/25 14:05:06 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**exe_env_cpy(char *envp[])
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
	return (env_array);
}
