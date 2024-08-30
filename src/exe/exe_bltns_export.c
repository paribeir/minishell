/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bltns_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:20:32 by jdach             #+#    #+#             */
/*   Updated: 2024/08/30 08:47:22 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define VALID_CHARACTERS_START "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRST\
UVWXYZ_"
#define VALID_CHARACTERS_LATER "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRST\
UVWXYZ0123456789_"

/*
 _=./minishell should be removed from the export. This will actually be
 _=/usr/bin/env when calling env.
*/

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

/*
 * @brief	Cheks the input of the export command for correct parameters.
 * @details
 * @param	cmd_list The current node of our command list.
 * @return	Returns 0 on success and -1 on error.
 */
int	exe_bltns_export_check_input(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '-')
		return (exe_err_long(ERR_BLTN_EXPORT_NO_OPTIONS), exe_set_status(1), 1);
	if (ft_strchr(VALID_CHARACTERS_START, s[0]) == 0)
		return (exe_err_long(ERR_EXPORT_INVALID_ID), exe_set_status(1), 1);
	while (s[++i] != '\0')
	{
		if (ft_strchr(VALID_CHARACTERS_LATER, s[i]) == 0)
			return (exe_err_long(ERR_EXPORT_INVALID_ID), exe_set_status(1), 1);
	}
	return (0);
}

void	exe_bltns_export_save_val(char *str, t_cmd *cmd_data)
{
	char	**str_arr;

	if (ft_strncmp(str, "=", 1) == 0)
	{
		exe_err_long(ERR_EXPORT_INVALID_ID);
		exe_set_status(1);
	}
	else if (ft_strchr(str, '='))
	{
		str_arr = ft_split(str, '=');
		if (exe_bltns_export_check_input(str_arr[0]) == 0)
			exe_env_set_var(str_arr[0], str_arr[1], cmd_data);
		exe_cleanup_strarray(str_arr);
	}
	else
		if (exe_bltns_export_check_input(str) == 0)
			exe_env_set_var(str, "", cmd_data);
}

void	exe_bltns_export(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	char	**cpy;
	int		i;

	g_status = 0;
	i = -1;
	if (cmd_list_item->arguments[0] == NULL)
	{
		cpy = exe_env_cpy(cmd_data->envp);
		exe_bltns_export_sort(cpy);
		exe_bltns_export_print(cpy);
		exe_cleanup_strarray(cpy);
	}
	else
		while (cmd_list_item->arguments[++i])
			exe_bltns_export_save_val(cmd_list_item->arguments[i], cmd_data);
}
