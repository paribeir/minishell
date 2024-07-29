/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:56:38 by jdach             #+#    #+#             */
/*   Updated: 2024/07/29 18:22:00 by jdach            ###   ########.fr       */
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

/*** Structs ***/

typedef struct s_cmd
{
	t_list	*nodes;
	int		pipe[2];
	int		saved_stdout;
	int		saved_stdin;
	char	**envp;
	int		pipe_status;
	int		fdout_status;
}	t_cmd;


/*** Functions ***/

void	exe_bin(t_cmd_list *cmd_list_item, t_cmd *cmd);
char	**exe_bin_args(char **original_args, char *binary);
char	*exe_bin_get_bin_path(t_cmd_list *cmd_list_item, t_cmd *cmd_env);
void	exe_bltns(t_cmd_list *cmd_list_item, t_cmd *cmd);
void	exe_bltns_cd(t_cmd_list *cmd_list_item, t_cmd *cmd_env);
void	exe_bltns_echo(t_cmd_list *cmd_list_item, t_cmd *cmd);
void	exe_bltns_env(t_cmd *cmd_env);
void	exe_bltns_export(t_cmd_list *cmd_list, t_cmd *env);
void	exe_bltns_pwd(t_cmd_list *cmd_list_item, t_cmd *cmd_env);
void	cleanup(t_cmd *cmd);
void	exe_err(char *err_msg, t_err_actn err_actn, t_cmd *cmd);
void	exe_directs(t_cmd_list *cmd_list_item, t_cmd *cmd);
void	exe_directs_append(t_cmd_list *cmd_list_item, t_cmd *cmd_env);
void	exe_directs_here_doc(t_cmd_list *cmd_list_item);
void	exe_directs_redir_in(t_cmd_list *cmd_list_item);
void	exe_directs_redir_out(t_cmd_list *cmd_list_item, t_cmd *cmd_env);
char	*exe_env_get_var_address(char *var, t_cmd *cmd_env);
char	*exe_env_get_var(char *var, t_cmd *cmd_env);
void	exe_env_init(t_cmd *cmd_env, char *envp[]);
int		exe_env_set_var(char *var, char *value, t_cmd *cmd_env);
void	exe_pipe_in(t_cmd *cmd_env);
void	exe_pipe_out(t_cmd *cmd_env);
void	exe(t_cmd_list	*cmd_list_item, t_cmd *cmd_env);

#endif
