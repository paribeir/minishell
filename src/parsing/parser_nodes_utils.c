/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:27:27 by patricia          #+#    #+#             */
/*   Updated: 2024/09/10 16:25:54 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_fusion(t_token *t)
{
	t_token	*token;
	int	flag;

	token = t;
	flag = 0;
	while (token)
	{
		if (token->type == IO_FILE || token->subtype == HEREDOC)
			redir_token_fusion(&token);
		else if (token->type == CMD_WORD)
		{
			token_fusion_cmdwords(&token);
			if (!token)
				continue ; 
			is_bltin(&token, flag);
			flag = 1;
			while (token && token->next && token->next->type == CMD_WORD)
				token = token->next;
		}
		if (token->type == PIPE || token->type == OPERATOR)
			flag = 0;
		token = token->next;
	}
	return (t);
}

void	token_fusion_cmdwords(t_token **token)
{
	while (*token && (*token)->type > PIPE)
	{
		if ((*token)->str[0])
		{
			(*token)->type = CMD_WORD;
			break ;
		}
		*token = (*token)->next;
	}
}

//cat redirs
void	redir_token_fusion(t_token **t)
{
	t_token	*token;
	t_token	*temp;

	token = *t;
	temp = NULL;
	free (token->str);
	token->str = ft_strdup(token->next->str);
	if (token->next->next)
	{
		temp = token->next->next;
		temp->prev = token;
	}
	free (token->next->str);
	free (token->next);
	token->next = temp;
}


//is this command a builtin?
void	is_bltin(t_token **token, int flag)
{
	if (flag || !(*token))
		return;
	(*token)->subtype = BINARY;
	if (!ft_strncmp("echo", (*token)->str, ft_strlen("echo") + 1))
		(*token)->subtype = BLTIN_ECHO;
	else if (!ft_strncmp("cd", (*token)->str, ft_strlen("cd") + 1))
		(*token)->subtype = BLTIN_CD;
	else if (!ft_strncmp("pwd", (*token)->str, ft_strlen("pwd") + 1))
		(*token)->subtype = BLTIN_PWD;
	else if (!ft_strncmp("export", (*token)->str, ft_strlen("export") + 1))
		(*token)->subtype = BLTIN_EXPORT;
	else if (!ft_strncmp("unset", (*token)->str, ft_strlen("unset") + 1))
		(*token)->subtype = BLTIN_UNSET;
	else if (!ft_strncmp("env", (*token)->str, ft_strlen("env") + 1))
		(*token)->subtype = BLTIN_ENV;
	else if (!ft_strncmp("exit", (*token)->str, ft_strlen("exit") + 1))
		(*token)->subtype = BLTIN_EXIT;
}

t_cmd_list	*create_cmd_node(t_token *token)
{
	t_cmd_list	*node;

	node = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (!node)
		return (NULL);
	node->type = token->subtype;
	node->binary = NULL;
	node->arguments = NULL;
	if (token->subtype == BINARY || token->subtype == BLTIN)
	{
		node->binary = ft_strdup(token->str);
		if (!node->binary)
		{
			ft_printf("Memory allocation error\n");
			return (NULL);
		}
	}
	if (token->subtype >= BLTIN || token->subtype == BINARY
		|| token->type == IO_FILE)
		add_arguments(token, &node);
	node->prev = NULL;
	node->next = NULL;
	return (node);
}
