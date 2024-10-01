/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:18:11 by paribeir          #+#    #+#             */
/*   Updated: 2024/10/01 19:27:32 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//empty the heredoc
//free everything
//reset to the initial minishell prompt
void	heredoc_signals_handler(int signum)
{
	write(1, "SIGINT received", 16);
	g_signum = signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDERR_FILENO, "\n", 1);
	rl_redisplay();
	rl_done = 1;
	//write(1, "hello", 6);
	return ;
}

void	heredoc_eof(int signum)
{
	(void)signum;
	write(1, "hello", 6);
}

void	heredoc_signals_set(void)
{
	signal(SIGINT, heredoc_signals_handler);
	signal(SIGQUIT, SIG_IGN);
}
