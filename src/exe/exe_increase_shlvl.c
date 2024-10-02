/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_increase_shlvl.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:24:23 by jdach             #+#    #+#             */
/*   Updated: 2024/10/02 16:24:42 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_increase_shlvl(t_cmd *cmd_data)
{
	char	*old_shlvl_str;
	int		old_shlvl;
	int		new_shlvl;
	char	*new_shlvl_str;

	old_shlvl_str = exe_env_get_var("SHLVL", cmd_data);
	old_shlvl = ft_atoi(old_shlvl_str);
	free(old_shlvl_str);
	new_shlvl = old_shlvl + 1;
	new_shlvl_str = ft_itoa(new_shlvl);
	exe_env_set_var("SHLVL", new_shlvl_str, cmd_data);
	free(new_shlvl_str);
}
