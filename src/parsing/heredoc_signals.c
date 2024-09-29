/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:18:11 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/29 21:18:24 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//empty the heredoc
//free everything
//reset to the initial minishell prompt
void	heredoc_signals_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signum = SIGINT;
		ft_putchar_fd('\n', STDOUT_FILENO);
		ft_putstr_fd(PURPLE "😈 > " NS, STDOUT_FILENO);
		return ;
	}
}

void	heredoc_signals_set(void)
{
	signal(SIGINT, heredoc_signals_handler);
	signal(SIGQUIT, SIG_IGN);
}
