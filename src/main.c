/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:27:29 by paribeir          #+#    #+#             */
/*   Updated: 2024/05/28 18:48:27 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[])
{
	if (argc == 2)
	{
		if (ft_strncmp(argv[1], "pat", 3) == 0)
			pat();
		else if (ft_strncmp(argv[1], "joh", 3) == 0)
			joh();
		else
			ft_putstr_fd("Use './minishell pat' or './minishell joh'\n", 2);
	}
	else
		ft_putstr_fd("Use './minishell pat' or './minishell joh'\n", 2);
	return (0);
}
