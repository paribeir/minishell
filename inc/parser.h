/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:32:10 by paribeir          #+#    #+#             */
/*   Updated: 2024/09/08 19:49:34 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"

/* EISTEE  < infile < infile2 < infile3 cat < infile4
typedef struct s_ast
{
	char			*binary;
	char			**arguments;
	t_token_type	type;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;
*/

typedef struct s_cmd_list
{
	t_token_subtype		type; //REDIN HEREDOC
	char				*binary; //"<<"
	char				**arguments; //temp_heredoc
	struct s_cmd_list	*prev;
	struct s_cmd_list	*next;
}	t_cmd_list;

typedef struct s_vars
{
	char	**var;
	char	**content;
}	t_vars;

/*** Functions ***/
//heredoc_utils.c
void	cleanup_memory(char *final_str, char *read_str, char *filename);
char	*heredoc_setup(t_token *token, char **final_str);
int	is_heredoc_delimiter(t_token *token, char *read_str);
char	*process_heredoc_line(char *read_str, t_token *token, t_cmd *cmd_data);
int	write_heredoc_to_file(char *filename, char *final_str);
int	handle_heredoc_delimiter(t_token *token, char *read_str, char *final_str, char *filename);

//heredoc.c
char	*heredoc_handler(t_token *token, t_cmd *cmd_data);
char	*expand_heredoc(char *str, t_cmd *cmd_data);
char *aux_str_join(char *str1, char *str2);


//quotes.c
int	quotes_check(t_token *token);
int	quotes_find_pair(char *str, int *i, char q);
void	quotes_remove(t_token **token);
int	var_in_squote(char *str);

//env_variables.c
void	expand_env_vars(t_token	*token, t_cmd *cmd_data);
void	add_expanded_var(char **current, char **str, t_cmd *cmd_data);
void	add_literal(char **current, char **str);
char	*get_var(char **str, t_cmd *cmd_data);

//expansions.c
void	variable_expansion(t_token **head, t_cmd *cmd_data);

//parser.c
t_cmd_list	*parse_tokens(t_token **token);
void	reorder_tokens(t_token *token, t_cmd_list **head, t_token_subtype type);
void	free_tokens(t_token **head);
void	node_add_back(t_cmd_list **head, t_cmd_list *new_node);
t_token	*token_fusion(t_token *t);
void	redir_token_fusion(t_token **t);
void	is_bltin(t_token **token, int flag);
t_cmd_list	*create_cmd_node(t_token *token);
void	add_arguments(t_token *token, t_cmd_list **node);
void	add_arguments_redirect(t_token *token, t_cmd_list **node);
int	count_args(t_token *token);
void	alloc_args(t_token *token, t_token *current, t_cmd_list **node, int nbr_args);
int	init_args(t_cmd_list **node, int nbr_args);
void	token_fusion_cmdwords(t_token **token);
void	add_arguments_redirect(t_token *token, t_cmd_list **node);



#endif
