/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 01:10:21 by jdach             #+#    #+#             */
/*   Updated: 2024/07/17 00:25:28 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_binary_path_search(char *binary)
{
	char	*appendix;
	char	**paths;
	char	*cached_ptr;
	char	*path;

	appendix = "/";
	paths = ft_split(getenv("PATH"), ':');
	while (*paths != NULL)
	{
		path = ft_strjoin(*paths, appendix);
		cached_ptr = path;
		path = ft_strjoin(path, binary);
		free(cached_ptr);
		if (access(path, F_OK) == 0)
			return (path);
		paths++;
	}
	ft_putstr_fd("No such bin\n", 2);
	return ("");
}

char	*get_binary_path_direct(char *binary)
{
	if (access(binary, F_OK) == 0)
		return (binary);
	else
	{
		ft_putstr_fd("No such bin", 2);
		exit (1);
	}
}

char	**set_execve_args(char **original_args, char *binary)
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

void	exe_bin(t_cmd_list *cmd_list_item, t_cmd *cmd)
{
	char	*path;
	char	**args;
	int		pid;

	if (ft_strchr(cmd_list_item->binary, '/') > 0)
		path = get_binary_path_direct(cmd_list_item->binary);
	else
		path = get_binary_path_search(cmd_list_item->binary);
	args = set_execve_args(cmd_list_item->arguments, cmd_list_item->binary);
	pid = fork();
	if (pid == 0)
		execve(path, args, NULL);
}
