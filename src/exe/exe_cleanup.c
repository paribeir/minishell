/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 20:32:53 by jdach             #+#    #+#             */
/*   Updated: 2024/09/28 17:10:17 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_cleanup(t_cmd *cmd_data)
{
	close(cmd_data->saved_stdin);
	close(cmd_data->saved_stdout);
	exe_cleanup_aftercmd(cmd_data);
	exe_cleanup_strarray(cmd_data->envp);
}
