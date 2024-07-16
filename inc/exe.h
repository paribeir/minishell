/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:56:38 by jdach             #+#    #+#             */
/*   Updated: 2024/07/16 22:17:16 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H

/* Need to include parser.h again to be able to use t_cmd_list struct*/
# include "parser.h"

/*** Error Messages ***/
# define ERR_ECHO_FLAGS "Only flag '-n' may be used with echo command\n"

/*** Enums ***/

typedef enum s_err_actn
{
	CLEANUP,
}	t_err_actn;


typedef enum s_node_type
{
	AND1,
	APPEND1,
	BLTN_CD1,
	BLTN_ECHO1,
	BLTN_EXPORT1,
	BLTN_UNSET1,
	BLTN_ENV1,
	BLTN_EXIT1,
	BLTN_PWD1,
	BIN1,
	HEREDOC1,
	M_EOF1,
	OR1,
	PIPE1,
	REDIR_IN1,
	REDIR_OUT1,
	VAR1,
}	t_node_type;


/*** Structs ***/

typedef struct s_node
{
	t_node_type		action;
	char			*binary;
	char			**params;
	char			**flags;
}	t_node;

typedef struct s_cmd
{
	t_list	*nodes;
	int		pipe[2];
}	t_cmd;


/*** Functions ***/

void	exe_append(t_cmd_list *cmd_list_item, t_cmd *cmd);
void	exe_bin(t_cmd_list *cmd_list_item, t_cmd *cmd);
void	exe_bltn_echo(t_cmd_list *cmd_list_item, t_cmd *cmd);
void	cleanup(t_cmd *cmd);
void	exe_err(char *err_msg, t_err_actn err_actn, t_cmd *cmd);
void	exe_get_in_out(t_cmd_list *cmd_list_item, t_cmd *cmd);
void	exe_here_doc(t_cmd_list *cmd_list_item, t_cmd *cmd);
int		exe_here_doc_fd(t_node *node, t_cmd *cmd, char	*dlmtr);
void	exe_init(t_cmd_list *cmd);
void	exe_look_ahead(t_cmd_list *cmd_list_item, t_cmd *cmd);
void	exe_redir_in(t_cmd_list *cmd_list_item, t_cmd *cmd);
void	exe_redir_out(t_cmd_list *cmd_list_item, t_cmd *cmd);
void	exe_run(t_cmd_list	*cmd_list);

#endif
