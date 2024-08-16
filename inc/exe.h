/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:56:38 by jdach             #+#    #+#             */
/*   Updated: 2024/08/16 18:31:50 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H

typedef struct s_cmd_list	t_cmd_list;
typedef struct s_cmd		t_cmd;

/*** Error Messages ***/

# define ERR_ECHO_FLAGS "Only flag '-n' may be used with echo command\n"

/*** Enums ***/

typedef enum s_err_actn
{
	CLEANUP,
}	t_err_actn;

/*** Functions ***/

void	exe_bin(t_cmd_list *cmd_list_item, t_cmd *cmd);
char	**exe_bin_args(char **original_args, char *binary);
char	*exe_bin_get_bin_path(t_cmd_list *cmd_list_item, t_cmd *cmd_data);
void	exe_bltns(t_cmd_list *cmd_list_item, t_cmd *cmd);
void	exe_bltns_cd(t_cmd_list *cmd_list_item, t_cmd *cmd_data);
void	exe_bltns_echo(t_cmd_list *cmd_list_item, t_cmd *cmd);
void	exe_bltns_env(char **envp);
void	exe_bltns_exit(t_cmd_list *cmd_list_item, t_cmd *cmd_data);
void	exe_bltns_export(t_cmd_list *cmd_list, t_cmd *env);
void	exe_bltns_pwd(t_cmd_list *cmd_list_item, t_cmd *cmd_data);
void	exe_bltns_unset(t_cmd_list *cmd_list_item, t_cmd *cmd_data);
void	exe_cleanup(t_cmd *cmd);
void	exe_cleanup_strarray(char **strarray);
void	exe_err(char *err_msg, t_err_actn err_actn, t_cmd *cmd);
void	exe_directs(t_cmd_list *cmd_list_item, t_cmd *cmd);
void	exe_directs_append(t_cmd_list *cmd_list_item, t_cmd *cmd_data);
void	exe_directs_here_doc(t_cmd_list *cmd_list_item);
void	exe_directs_redir_in(t_cmd_list *cmd_list_item);
void	exe_directs_redir_out(t_cmd_list *cmd_list_item, t_cmd *cmd_data);
char	*exe_env_get_var_address(char *var, t_cmd *cmd_data);
char	*exe_env_get_var(char *var, t_cmd *cmd_data);
char	**exe_env_cpy(char *envp[]);
int		exe_env_set_var(char *var, char *value, t_cmd *cmd_data);
void	exe_pipe_in(t_cmd *cmd_data);
void	exe_pipe_out(t_cmd *cmd_data);
void	exe_signals_responsive(t_cmd_list *cmd_list_item, t_cmd *cmd_data);
void	exe(t_cmd_list	*cmd_list_item, t_cmd *cmd_data);

#endif
