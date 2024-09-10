/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:39:37 by patricia          #+#    #+#             */
/*   Updated: 2024/09/10 15:07:38 by paribeir         ###   ########.fr       */
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
		ft_printf("Malloc error in quote removal\n");
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
	t_token *current = *token;
	int	in_squote;
	int	in_dquote;
	char	*new_str;

	in_squote = 0;
	in_dquote = 0;
	new_str = allocate_new_str(ft_strlen(current->str));
	if (!new_str) 
		return ;
	del_quotes(new_str, current->str, &in_squote, &in_dquote);	
	ft_strlcpy(current->str, new_str, ft_strlen(current->str) + 1);	
	free(new_str);
}

//TO DO--> Handle malloc error
/*void	quotes_remove(t_token **token)
{
	int	i;
	int j;
	char *new_str;
	int	in_squote;
	int	in_dquote;
	t_token	*current;

	current = *token;
	new_str = (char *)ft_calloc(ft_strlen(current->str) + 1, sizeof(char));
	if (!new_str)
	{
		ft_printf("Malloc error in quote removal\n");
		return ;
	}
	i = 0;
	j = 0;
	in_squote = 0;
	in_dquote = 0;
	while (current->str[i])
	{
		if (current->str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (current->str[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		else
			new_str[j++] = current->str[i];
		i++;
	}
	ft_strlcpy(current->str, new_str, ft_strlen(current->str) + 1);
	free (new_str);
}*/
