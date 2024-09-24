/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cleanup_strarray.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 22:18:28 by jdach             #+#    #+#             */
/*   Updated: 2024/09/16 16:36:22 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_cleanup_strarray(char **strarray)
{
	int	i;

	i = 0;
	if (strarray)
	{
		while (strarray[i] != NULL)
		{
			free (strarray[i]);
			strarray[i] = NULL;
			i++;
		}
		//free (strarray[i]);
		free (strarray);
		strarray = NULL;
	}
}
