/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bltns_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:20:32 by jdach             #+#    #+#             */
/*   Updated: 2024/07/26 16:59:10 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @brief	Cheks the input of the export command for correct parameters.
 * @details
 * @param	cmd_list The current node of our command list.
 * @return	Returns 0 on success and -1 on error.
 */
int	exe_bltns_export_check_input(t_cmd_list *cmd_list)
{
	char	*a;
	char	**str_array;

	if (cmd_list->arguments && cmd_list->arguments[0][0] == '-')
		return (perror("export: Minshell allows no options"), 1);
	str_array = ft_split(cmd_list->arguments[0], '=');
	a = str_array[0];
	while (*a != '\0')
	{
		if (*a < 65 || *a > 122 || (*a > 90 && *a < 97 && *a != 95))
			return (perror("export: not valid in this context"), 1);
		a++;
	}
	return (0);
}

void	exe_bltns_export(t_cmd_list *cmd_list, t_cmd *env)
{
	char	**str_arr;

	str_arr = ft_split(cmd_list->arguments[0], '=');
	if (exe_bltns_export_check_input(cmd_list) == 0)
		exe_env_set_var(str_arr[0], str_arr[1], env);
}
