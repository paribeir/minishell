/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:00:07 by paribeir          #+#    #+#             */
/*   Updated: 2024/06/27 20:37:29 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/tokenizer.h"
#include "../inc/parser.h"

t_cmd_list	*parse_tokens(t_token *token)
{
	t_token		*current;
	t_cmd_list	*node;

	current = token_fusion(token);
	if (!current)
		return (NULL);
	while (current)
	{
		node = create_node(current);
	}
	return (node);
}

//heredoc's delimiter is also stored in the str variable
//expansion was already taken of, I suppose
t_token	*token_fusion(t_token	*token)
{
	t_token	*temp;

	if (token->type == IO_FILE && token->subtype != HEREDOC)
	{
		token->str = ft_strdup(token->next->str);
		temp = token->next->next;
		//delete next token;
		token->next = temp;
	}
	else if (token->subtype == HEREDOC)
	{
		
	}


	

}

//Store VAR= in a linked list
void	get_variable(char *str)
{
	char *start;

	start = ft_strchr(str, '=');

}



void expansions(t_token *token, char *str)
{
	int	i;
	char	*new_str;

	i = 0;
	if (token)
		str = token->str;
	heredoc_handler(token);
	if (ft_strchr(str, '$'))
	{
		//expand
	}
	here_handler(token);
}

//--> Add return value if gnl fails
int	heredoc_handler(t_token *token)
{
	char	*read_str;
	char	*final_str;
	int		fd;

	final_str = "";
	read_str = ft_get_next_line(0);
	while (read_str)
	{
		if (ft_strncmp(token->next->str, read_str, \
		ft_strlen(token->next->str)) == 0 && \
		read_str[ft_strlen(token->next->str) + 1] == '\0')
		{
			fd = open("here_doc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
			ft_putstr_fd(final_str, fd);
			free(final_str);
			free(read_str);
			close(fd);
			return ("here_doc_temp");
		}
		ft_strjoin(final_str, read_str);
		free (read_str);
		read_str = ft_get_next_line(0);
		expand_var();
		//EXPAND: VARIABLES ONLY! $VAR
	}
}
