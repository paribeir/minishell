/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:18:11 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/29 14:51:45 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	heredoc_signals_handler(int signum)
{
	if (signum == SIGINT)
	{
		return ;
		//empty the heredoc
		//free everything
		//reset to the initial minishell prompt
	}
}

void	heredoc_signals_set(void)
{
	signal(SIGINT, heredoc_signals_handler);
	signal(SIGQUIT, SIG_IGN);
}
