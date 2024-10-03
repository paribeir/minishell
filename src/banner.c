/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:09:06 by paribeir          #+#    #+#             */
/*   Updated: 2024/10/02 17:22:13 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	banner(void)
{
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(RED "	      (_)L|J   \n" NS, STDERR_FILENO);
	ft_putstr_fd(RED "       )      (\") |  (_)    (\n" NS, STDERR_FILENO);
	ft_putstr_fd(RED "       ,(. A `/ \\-|  /\"\\   (,`)\n" NS, STDERR_FILENO);
	ft_putstr_fd(RED "      )' (' \\/\\ / | .-T-.  ) (.\n" NS, STDERR_FILENO);
	ft_putstr_fd(RED "     (' ),).  _W_ |  _H_  (,)' )\n" NS, STDERR_FILENO);
	ft_putstr_fd(RED "    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n" NS, STDERR_FILENO);
	ft_putstr_fd(BOLD "      🔥 Welcome to MiniHell 🔥\n" NS, STDERR_FILENO);
	ft_putstr_fd(RED "    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n" NS, STDERR_FILENO);
	ft_putstr_fd(BOLD "      > by: jdach & paribeir <\n" NS, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
