/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:39:37 by patricia          #+#    #+#             */
/*   Updated: 2024/10/02 14:37:29 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// malloc the new string
char	*allocate_new_str(size_t len)
{
	char	*new_str;

	new_str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!new_str) 
	{
		ft_putstr_fd("minishell: malloc error\n", STDERR_FILENO);
		return (NULL);
	}
	return (new_str);
}

// remove quotes and copy chars to new_str
void	del_quotes(char *new_str, char *src_str, int *in_squote, int *in_dquote)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src_str[i]) 
	{
		if (src_str[i] == '\'' && !(*in_dquote))
			*in_squote = !(*in_squote);
		else if (src_str[i] == '\"' && !(*in_squote))
			*in_dquote = !(*in_dquote);
		else
			new_str[j++] = src_str[i];
		i++;
	}
}

void	quotes_remove(t_token **token)
{
	t_token	*current;
	int		in_squote;
	int		in_dquote;
	int		len;
	char	*new_str;

	current = *token;
	in_squote = 0;
	in_dquote = 0;
	if (!current || !current->str)
		return ;
	len = ft_strlen(current->str);
	new_str = allocate_new_str(len);
	if (!new_str) 
		return ;
	del_quotes(new_str, current->str, &in_squote, &in_dquote);
	ft_strlcpy(current->str, new_str, ft_strlen(new_str) + 1);
	free(new_str);
}

char	*quotes_remove_one_var(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = allocate_new_str(ft_strlen(str));
	if (!new_str) 
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\"')
		i++;
	i++;
	while (str[i]) 
	{
		if (str[i] == '\"')
			break ;
		else
			new_str[j++] = str[i];
		i++;
	}
	return (new_str);
}
