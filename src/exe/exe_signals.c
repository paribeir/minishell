/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:58:51 by jdach             #+#    #+#             */
/*   Updated: 2024/08/16 19:03:20 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_signals_nl(int signum)
{
	(void) signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", STDERR_FILENO);
	rl_redisplay();
}

void	exe_signals_responsive(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	signal(SIGINT, exe_signals_nl);
	signal(SIGQUIT, SIG_IGN);
}
