/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:58:51 by jdach             #+#    #+#             */
/*   Updated: 2024/10/02 13:38:31 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_signals_reinitiate_readline(int signum)
{
	g_signum = signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", STDERR_FILENO);
	rl_redisplay();
}

void	exe_signals_processing_handler(int signum)
{
	g_signum = signum;
	if (signum == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)", 2);
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
}

void	exe_signals_default(void)
{
	signal(SIGINT, exe_signals_reinitiate_readline);
	signal(SIGQUIT, SIG_IGN);
}

void	exe_signals_processing(void)
{
	signal(SIGINT, exe_signals_processing_handler);
	signal(SIGQUIT, exe_signals_processing_handler);
}
