/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bltns_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:24:36 by jdach             #+#    #+#             */
/*   Updated: 2024/09/29 15:46:48 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_bltns_env(char **envp, t_cmd *cmd_data)
{
	int	i;

	cmd_data->exit_code = 0;
	i = 0;
	while (envp[i] != NULL)
		ft_printf("%s\n", envp[i++]);
}
