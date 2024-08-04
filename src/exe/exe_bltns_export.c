/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bltns_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:20:32 by jdach             #+#    #+#             */
/*   Updated: 2024/08/04 10:07:48 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 _=./minishell should be removed from the export. This will actually be
 _=/usr/bin/env when calling env.
*/

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

void	exe_bltns_export_print(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		ft_printf("%s \n", envp[i++]);
}

void	exe_bltns_export_sort(char **cpy)
{
	char	*tmp_ptr;
	int		still_sorting;
	int		i;

	still_sorting = 1;
	while (still_sorting == 1)
	{
		still_sorting = 0;
		i = -1;
		while (cpy[++i] && cpy[i + 1])
		{
			if (ft_strncmp(cpy[i], cpy[i + 1], ft_strlen(cpy[i])) > 0)
			{
				tmp_ptr = cpy[i];
				cpy[i] = cpy[i + 1];
				cpy[i + 1] = tmp_ptr;
				still_sorting = 1;
			}
		}
	}
}

void	exe_bltns_export(t_cmd_list *cmd_list, t_cmd *cmd_data)
{
	char	**str_arr;
	char	**cpy;

	if (cmd_list->arguments[0] == NULL)
	{
		cpy = exe_env_cpy(cmd_data->envp);
		exe_bltns_export_sort(cpy);
		exe_bltns_export_print(cpy);
		exe_cleanup_strarray(cpy);
	}
	else
	{
		str_arr = ft_split(cmd_list->arguments[0], '=');
		if (exe_bltns_export_check_input(cmd_list) == 0)
			exe_env_set_var(str_arr[0], str_arr[1], cmd_data);
	}
}
