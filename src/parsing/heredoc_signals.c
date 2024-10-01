/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:18:11 by paribeir          #+#    #+#             */
/*   Updated: 2024/10/01 22:03:15 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//empty the heredoc
//free everything
//reset to the initial minishell prompt
void	heredoc_signals_handler(int signum)
{
	g_signum = signum;
	rl_done = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDERR_FILENO, "\n", 1);
	rl_redisplay();
}

void	heredoc_signals_set(void)
{
	signal(SIGINT, heredoc_signals_handler);
	signal(SIGQUIT, SIG_IGN);
}
