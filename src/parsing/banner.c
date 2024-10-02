/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:09:06 by paribeir          #+#    #+#             */
/*   Updated: 2024/10/02 15:08:58 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	banner(void)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	ft_putstr_fd(RED "	      (_)L|J   \n" NS, STDOUT_FILENO);
	ft_putstr_fd(RED "       )      (\") |  (_)    (\n" NS, STDOUT_FILENO);
	ft_putstr_fd(RED "       ,(. A `/ \\-|  /\"\\   (,`)\n" NS, STDOUT_FILENO);
	ft_putstr_fd(RED "      )' (' \\/\\ / | .-T-.  ) (.\n" NS, STDOUT_FILENO);
	ft_putstr_fd(RED "     (' ),).  _W_ |  _H_  (,)' )\n" NS, STDOUT_FILENO);
	ft_putstr_fd(RED "    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n" NS, STDOUT_FILENO);
	ft_putstr_fd(BOLD "      🔥 Welcome to MiniHell 🔥\n" NS, STDOUT_FILENO);
	ft_putstr_fd(RED "    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n" NS, STDOUT_FILENO);
	ft_putstr_fd(BOLD "      > by: jdach & paribeir <\n" NS, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}
