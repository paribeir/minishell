/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:32:10 by paribeir          #+#    #+#             */
/*   Updated: 2024/06/25 22:16:34 by paribeir         ###   ########.fr       */
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
	t_token_type	type;
	t_token_subtype	subtype;
	char			*cmd_word;
	char			**arguments;
	char			**flags;
	struct s_command	*prev;
	struct s_command	*next;
}	t_cmd_list;

#endif
