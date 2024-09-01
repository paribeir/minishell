/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patricia <patricia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:24:20 by patricia          #+#    #+#             */
/*   Updated: 2024/09/01 21:52:54 by patricia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_arguments_redirect(t_token *token, t_cmd_list **node)
{
	(*node)->arguments = (char **)malloc(2 * sizeof(char *));
	if (!(*node)->arguments)
	{
		ft_printf("Malloc error");
		return ;
	}
	(*node)->arguments[0] = ft_strdup(token->str);
	if (!(*node)->arguments[0])
	{
		ft_printf("String duplication error");
		return ;
		free((*node)->arguments);
		(*node)->arguments = NULL;
	}
	(*node)->arguments[1] = NULL;
	return ;
}

int	count_args(t_token *token)
{
	int	args;
	t_token	*current;

	args = 0;
	current = token->next;
	while (current && current->type > PIPE)
	{
		if (current->subtype == 0)
			args++;
		current = current->next;
	}
	return (args);
}

int	init_args(t_cmd_list **node, int nbr_args)
{
	(*node)->arguments = (char **)malloc((nbr_args + 1) * sizeof(char *));
	if (!(*node)->arguments)
	{
	    ft_printf("Malloc error\n");
	    return (1);
	}
	return (0);
}

int	duplicate_args(char **arguments, int *i, char *str)
{
	arguments[*i] = ft_strdup(str);
	if (!arguments[*i])
	{
		ft_printf("String duplication error\n");
		while (*i > 0)
			free(arguments[--(*i)]);
		free(arguments);
		return (1); 
	}
	(*i)++;
	return (0);
}

void	alloc_args(t_token *token, t_token *current, t_cmd_list **node, int nbr_args)
{
	int i;

	i = 0;	
	current = token->next;
	if (init_args(node, nbr_args))
		return ;
	while (current && current->type > PIPE)
	{
		if (!(current->subtype == 0 && !current->str[0]) && 
		(current->subtype == 0 || current->subtype == SQUOTE || current->subtype == DQUOTE))
		{
			if (duplicate_args((*node)->arguments, &i, current->str))
			{
				(*node)->arguments = NULL;
				return ;
			}
		}
		current = current->next;
	}	
	(*node)->arguments[i] = NULL;
}
