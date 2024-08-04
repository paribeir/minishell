/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bltns_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:24:36 by jdach             #+#    #+#             */
/*   Updated: 2024/08/04 10:07:47 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_bltns_pwd(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	char	*pwd_str;

	pwd_str = exe_env_get_var("PWD", cmd_data);
	printf("%s \n", pwd_str);
}
