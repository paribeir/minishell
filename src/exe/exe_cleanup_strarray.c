/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cleanup_strarray.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 22:18:28 by jdach             #+#    #+#             */
/*   Updated: 2024/08/22 17:14:44 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_cleanup_strarray(char **strarray)
{
	int	i;

	i = -1;
	if (strarray)
	{
		while (strarray[++i] != NULL)
			free (strarray[i]);
		free (strarray[i]);
		free (strarray);
	}
}
