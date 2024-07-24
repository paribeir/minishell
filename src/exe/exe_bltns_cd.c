/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bltns_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:24:36 by jdach             #+#    #+#             */
/*   Updated: 2024/07/24 17:02:24 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_bltns_cd(t_cmd_list *cmd_list_item, t_cmd *cmd_env)
{
	exe_env_set_var("OLDPWD", exe_env_get_var("PWD", cmd_env), cmd_env);
	exe_env_set_var("PWD", cmd_list_item->arguments, cmd_env);
}
