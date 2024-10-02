/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:18:11 by paribeir          #+#    #+#             */
/*   Updated: 2024/10/02 14:58:42 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//SIGINT needs to free everything and reset to the initial minishell prompt
void	heredoc_signals_handler(int signum)
{
	g_signum = signum;
	rl_done = 1;
	write(STDERR_FILENO, "\n", 1);
	ioctl(1, TIOCSTI, "");
}

void	heredoc_signals_set(void)
{
	signal(SIGINT, heredoc_signals_handler);
	signal(SIGQUIT, SIG_IGN);
}
