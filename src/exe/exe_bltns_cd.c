/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bltns_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:24:36 by jdach             #+#    #+#             */
/*   Updated: 2024/07/25 18:33:39 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exe_bltns_cd_get_target(char *parameter, t_cmd *cmd_env)
{
	char	*target;
	char	*tmp_ptr;

	target = exe_env_get_var("PWD", cmd_env);
	if (parameter[0] == '/')
		target = ft_strdup(parameter);
	else if (parameter[0] == '-' && parameter[1] == '\0')
		target = exe_env_get_var("OLDPWD", cmd_env);
	else
	{
		tmp_ptr = target;
		target = ft_strjoin(target, "/");
		free(tmp_ptr);
		tmp_ptr = target;
		target = ft_strjoin(target, parameter);
		free(tmp_ptr);
	}
	return (target);
}

int	exe_bltns_cd_check_input(t_cmd_list *cmd_list_item)
{
	if (cmd_list_item->arguments[1])
		perror("minishell: cd: too many arguments");
	return (0);
}

void	exe_bltns_cd(t_cmd_list *cmd_list_item, t_cmd *cmd_env)
{
	char	*target;

	exe_bltns_cd_check_input(cmd_list_item);
	target = exe_bltns_cd_get_target(cmd_list_item->arguments[0], cmd_env);
	if (chdir(target) == 0)
	{
		exe_env_set_var("OLDPWD", exe_env_get_var("PWD", cmd_env), cmd_env);
		exe_env_set_var("PWD", target, cmd_env);
	}
	else
		perror("no such file or directory");
}
