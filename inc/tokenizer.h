/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:11:46 by paribeir          #+#    #+#             */
/*   Updated: 2024/06/27 19:17:10 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

/*** Macros ***/
//IFS stands for Internal Field Separator
# define IFS		" \t\n"
# define SPECIAL_CHARS	"|&<>();#!"

/*** enum ***/
typedef enum s_token_type {
	OPERATOR = 101,
	PIPE = 102,
	CMD_WORD = 103,
	IO_FILE = 104,
}	t_token_type;

typedef enum s_token_subtype {
	UNKNOWN,
	T_PIPE,
	SQUOTE,
	DQUOTE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	AND_IF,
	OR_IF,
	VAR_ASSIGN,
	TOKEN_EOF,
	WILDCARD,
}	t_token_subtype;

/*** Linked list - Tokens ***/
typedef struct s_token {
	t_token_type	type;
	t_token_subtype	subtype;
	char			*str;
	int				length;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

/*** Functions ***/
t_token	*tokenizer(char *input);
int		token_small(char *input, t_token *token);
int		token_big(char *start, t_token *token);
void	add_token(char *start, t_token **head, t_token *token);
void	TEST_printf_stuff(t_token **head);

/*** Token Utils***/
t_token	*create_token(void);
void	token_add_back(t_token **head, t_token *new_node);
int	subtype_check(char q, char *input);
int	check_syntax(t_token **head);



/*
	COMMAND,
	ARGUMENT,
	FLAG,
	PIPE,
	VARIABLE,
	EXIT_VAL,
	REDIRECTION,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	TOKEN_SPACE,
	OPERATOR,
	WILDCARD,
	TOKEN_EOF,
*/

#endif
