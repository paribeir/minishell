/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 20:23:33 by jdach             #+#    #+#             */
/*   Updated: 2024/09/03 18:10:56 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_err_long(char *meta, char *err_str)
{
	ft_putstr_fd("minishell: ", 2);
	if (meta)
	{
		ft_putstr_fd(meta, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(err_str, 2);
	ft_putstr_fd("\n", 2);
}
