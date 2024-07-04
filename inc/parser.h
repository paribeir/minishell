/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:32:10 by paribeir          #+#    #+#             */
/*   Updated: 2024/07/04 20:11:39 by paribeir         ###   ########.fr       */
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
	t_token_type		type; //IO_FILE
	t_token_subtype		subtype; //REDIN HEREDOC
	char				*cmd_word; //"<<"
	char				**arguments; //temp_heredoc
	char				**flags; //NULL
	struct s_cmd_list	*prev; 
	struct s_cmd_list	*next;
}	t_cmd_list;

typedef struct s_vars
{
	char	**var;
	char	**content;
}	t_vars;

/*** Functions ***/
//heredoc.c
char	*heredoc_handler(t_token *token);

//quotes.c
int	quotes_check(t_token *token);
int	quotes_find_pair(char *str, int *i, char q);
void	quotes_remove(t_token *token);




#endif
