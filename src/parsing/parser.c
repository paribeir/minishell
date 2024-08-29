/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:00:07 by paribeir          #+#    #+#             */
/*   Updated: 2024/08/29 15:11:18 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TO DO: End function "create cmd node" by finishing "get_arguments"
//pipes and operators are not being correctly added to the linked list
t_cmd_list	*parse_tokens(t_token **token)
{
	t_token		*current;
	t_cmd_list	*head;

	head = NULL;
	current = token_fusion(*token);
	if (!current)
		return (NULL);
	while (current)
	{
		reorder_tokens(current, &head, REDIR_IN);
		while (current && current->type != PIPE && current->type != OPERATOR)
			current = current->next;
		if (current)
		{
			node_add_back(&head, create_cmd_node(current));
			current = current->next;
		}
	}
	free_tokens(token);
	return (head);
}

void	reorder_tokens(t_token *token, t_cmd_list **head, t_token_subtype type)
{
	t_cmd_list	*node;
	t_token		*current;
	int			flag;

	current = token;
	while (current && current->type > PIPE)
	{
		flag = 0;
<<<<<<< HEAD
		if (current->subtype == type || (current->subtype == HEREDOC && type == REDIR_IN) ||
			(current->subtype == REDIR_APPEND && type == REDIR_OUT) ||
			(current->subtype >= BLTIN && type == BINARY))
=======
		(void) type;
		if (current->subtype != ARGUMENT && current->subtype != DQUOTE && current->subtype != SQUOTE)
>>>>>>> noreorder
			flag = 1;
		if (flag)
		{
			node = create_cmd_node(current);
			if (!node)
			{
				ft_printf("Failed to create node\n");
				break ;
			}
			node_add_back(head, node);
		}
		current = current->next;
	}
}

/*free the initial linked list of tokens*/
void	free_tokens(t_token **head)
{
	t_token	*current;
	t_token	*temp;

	current = *head;
	while (current)
	{
		temp = current;
		current = current->next;
		if (temp->str)
			free(temp->str);
		free(temp);
	}
	*head = NULL;
}

void	node_add_back(t_cmd_list **head, t_cmd_list *new_node)
{
	t_cmd_list	*temp;


	if (!*head)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
		new_node->prev = temp;
	}
}

/*no need to check for token->next since that is one of the checks in parsing
(a redirect must be followed by a filename)*/
t_token	*token_fusion(t_token	*t)
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
			is_bltin(&token, flag);
			flag = 1;
			while (token->next && token->next->type == CMD_WORD)
				token = token->next;
		}
		if (token->type == PIPE || token->type == OPERATOR)
			flag = 0;
		token = token->next;
	}
	return (t);
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
	free (token->next);
	token->next = temp;
}


//is this command a builtin?
void	is_bltin(t_token **token, int flag)
{
	if (flag)
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

//get and assign arguments, delete argument tokens
void	add_arguments(t_token *token, t_cmd_list **node)
{
	int		nbr_args;
	t_token	*current;

	current = NULL;
	nbr_args = 0;
	if (token->type == IO_FILE) //redirects
	{
		add_arguments_redirect (token, node);
		return ;
	}
	else if (token->next) //if its a binary and there is something afterwards
		nbr_args = count_args(token);
	alloc_args(token, current, node, nbr_args);
}

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

void	alloc_args(t_token *token, t_token *current, t_cmd_list **node, int nbr_args)
{
	int	i;

	i = 0;
	current = token->next;
	if (init_args(node, nbr_args))
		return ;
	while (current && current->type > PIPE)
	{
	    if (current->subtype == 0)
	    {
	        (*node)->arguments[i] = ft_strdup(current->str);
	        if (!(*node)->arguments[i])
	        {
	            ft_printf("String duplication error\n");
	            while (i > 0)
	                free((*node)->arguments[--i]);
	            free((*node)->arguments);
	            (*node)->arguments = NULL;
	            return ;
	        }
	        i++;
	    }
	    current = current->next;
	}
	(*node)->arguments[i] = NULL;
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
