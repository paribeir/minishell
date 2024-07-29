/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 20:23:33 by jdach             #+#    #+#             */
/*   Updated: 2024/07/29 22:21:14 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_err(char *err_msg, t_err_actn err_actn, t_cmd *cmd)
{
	perror(err_msg);
	if (err_actn == CLEANUP)
		exe_cleanup (cmd);
}
