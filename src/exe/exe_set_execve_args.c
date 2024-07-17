/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_set_execve_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:52:59 by jdach             #+#    #+#             */
/*   Updated: 2024/07/17 17:53:20 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**exe_set_execve_args(char **original_args, char *binary)
{
	int		i;
	int		j;
	char	**execve_args;

	i = 0;
	j = 0;
	while (original_args[i] != NULL)
		i++;
	execve_args = (char **)malloc((i + 2) * sizeof(char *));
	execve_args[j++] = binary;
	while (j <= i)
	{
		execve_args[j] = original_args[j - 1];
		j++;
	}
	execve_args[j] = NULL;
	return (execve_args);
}
