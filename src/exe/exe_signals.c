/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:58:51 by jdach             #+#    #+#             */
/*   Updated: 2024/08/17 09:21:47 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_signals_reinitiate_readline(int signum)
{
	(void) signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", STDERR_FILENO);
	rl_redisplay();
}

void	exe_signals_refresh_readline(int signum)
{
	if (signum == SIGQUIT)
		ft_printf("Quit (core dumped)");
	write(1, "\n", STDERR_FILENO);
	rl_on_new_line();
}

void	exe_signals_default(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	signal(SIGINT, exe_signals_reinitiate_readline);
	signal(SIGQUIT, SIG_IGN);
}

void	exe_signals_processing(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	signal(SIGINT, exe_signals_refresh_readline);
	signal(SIGQUIT, exe_signals_refresh_readline);
}
