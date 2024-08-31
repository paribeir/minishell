/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bltns_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:24:36 by jdach             #+#    #+#             */
/*   Updated: 2024/08/31 07:49:09 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exe_bltns_cd_get_target(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	char	*target;
	char	**args;

	args = cmd_list_item->arguments;
	if (*args == NULL)
		target = exe_env_get_var("HOME", cmd_data);
	else if (args[0][0] == '-' && args[0][1] == '\0')
		target = exe_env_get_var("OLDPWD", cmd_data);
	else
		target = ft_strdup(args[0]);
	return (target);
}

int	exe_bltns_cd_check_input(t_cmd_list *cmd_list_item)
{
	if (cmd_list_item->arguments[1])
	{
		exe_err_long(ERR_CD_TOO_MANY_ARGS);
		g_status = 1;
	}
	return (0);
}

void	exe_bltns_cd(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	char	*target;
	char	pwd[PATH_MAX];
	char	*pwd_allocated;

	g_status = 0;
	exe_bltns_cd_check_input(cmd_list_item);
	target = exe_bltns_cd_get_target(cmd_list_item, cmd_data);
	if (chdir(target) == 0)
	{
		exe_env_set_var("OLDPWD", exe_env_get_var("PWD", cmd_data), cmd_data);
		getcwd(pwd, sizeof(pwd));
		pwd_allocated = ft_strdup(pwd);
		exe_env_set_var("PWD", pwd_allocated, cmd_data);
	}
	else
	{
		g_status = 1;
		exe_err_long(ERR_CD_NO_SUCH_DIRECTORY);
	}
	free(target);
}
