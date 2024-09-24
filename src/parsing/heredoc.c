/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:49:00 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/23 07:26:24 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//--> TO-DO: Add return value if gnl fails
//eval if we need a check before quote removal
//Does this work with more than one heredoc?

char	*heredoc_setup(t_token *token, char **final_str)
{
	*final_str = ft_strdup("");
	quotes_remove(&token->next);
	return (hex_to_dec(token));
}

int	update_final_str(char **final_str, char *read_str, char *filename)
{
	char	*temp_str;

	temp_str = ft_strjoin(*final_str, read_str);
	if (!temp_str)
	{
		cleanup_memory(*final_str, read_str, filename);
		return (0);  // Handle strjoin failure
	}
	free(*final_str);
	*final_str = temp_str;
	return (1);  // Success
}

void	cleanup_memory(char *final_str, char *read_str, char *filename)
{
	if (final_str)
		free(final_str);
	if (read_str)
		free(read_str);
	if (filename)
		free(filename);
}

//add signal handling
int	process_heredoc_loop(t_token *token, t_cmd *cmd_data, char **final_str, char *filename)
{
	char	*read_str;

	read_str = ft_get_next_line(0);
	while (read_str)
	{
		if (handle_heredoc_delimiter(token, read_str, *final_str, filename))
			return (1);
		read_str = process_heredoc_line(read_str, token, cmd_data);
		if (!update_final_str(final_str, read_str, filename))
			return (0);
		free(read_str);
		ft_putstr_fd("heredoc > ", STDOUT_FILENO);
		read_str = ft_get_next_line(0);
	}
	return (0);
}
char	*heredoc_handler(t_token *token, t_cmd *cmd_data)
{
	char	*final_str;
	char	*filename;

	ft_putstr_fd("heredoc > ", STDOUT_FILENO);
	filename = heredoc_setup(token, &final_str);
	if (!final_str || !filename)
		return (cleanup_memory(final_str, NULL, filename), NULL);
	if (!process_heredoc_loop(token, cmd_data, &final_str, filename))
		return (cleanup_memory(final_str, NULL, filename), NULL);
	return (filename);
}


//expanding env vars knowing there are no single quotes
char	*expand_heredoc(char *str, t_cmd *cmd_data)
{
	char	*sum;
	char	*before_var;
	char	*dollar;
	char	*var_value;
	char	*next_dollar;

	sum = ft_strdup("");
	dollar = str;
	while (dollar && *dollar)
	{
		next_dollar = ft_strchr(dollar, '$');
		if (!next_dollar)
		{
			sum = aux_str_join(sum, dollar);
			break ;
		}
		before_var = ft_substr(dollar, 0, next_dollar - dollar);
		sum = aux_str_join(sum, before_var);
		var_value = get_var(&next_dollar, cmd_data);
		sum = aux_str_join(sum, var_value);
		free(var_value);
		free(before_var);
		dollar = next_dollar;
	}
	return (sum);
}

/*char *aux_str_join(char *str1, char *str2)
{
    char *temp;

    temp = ft_strjoin(str1, str2);
    if (!temp)
        return (NULL);
    if (str1)
        free(str1);
    return (temp);
}*/
char *aux_str_join(char *str1, char *str2)
{
    char *temp;

    // If str1 is NULL, just return a copy of str2
    if (!str1)
        return (ft_strdup(str2)); // Assuming ft_strdup duplicates the string

    // If str2 is NULL, return str1 unchanged
    if (!str2)
        return (str1);

    // Join str1 and str2 into a new allocated string
    temp = ft_strjoin(str1, str2);
    if (!temp)
        return (NULL); // Return NULL if allocation failed

    // Free the old str1 as it's no longer needed
    free(str1);
    
    return (temp);
}

