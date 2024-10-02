/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:27:56 by paribeir          #+#    #+#             */
/*   Updated: 2024/10/02 14:53:24 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include "../lib/libft/libft.h"
# include "exe.h"
# include "tokenizer.h"
# include "parser.h"

extern int	g_signum;

/*** Structs ***/
typedef struct s_exit_status
{
	int	exit_status;
	int	pid;
}	t_exit_status;

typedef struct s_cmd
{
	int			saved_stdin;
	int			saved_stdout;
	int			pipe[2];
	int			tmp_read_pipe_fd;
	int			wr_to_pipe;
	int			rd_from_pipe;
	char		**envp;
	int			pipe_scenario;
	int			subshell_running;
	int			stop_exe;
	int			exit_code;
	t_list		*exit_codes;
	t_cmd_list	*cmd_list_head;
}	t_cmd;

/*** Error Messages ***/
# define ERR_ECHO_FLAGS "Only flag '-n' may be used with echo command\n"
# define ERR_EXPORT_INVALID_ID "not a valid identifier"
# define ERR_CD_TOO_MANY_ARGS "too many arguments"
# define ERR_CD_NO_SUCH_DIRECTORY "No such file or directory"
# define ERR_EXIT_NO_NBR "numeric argument required"
# define ERR_TOO_MANY_ARGS "too many arguments"
# define ERR_FD_NO_SUCH_FILE "No such file or directory"
# define ERR_FD_NOT_READABLE "Permission denied"
# define ERR_FD_NOT_WRITABLE "Permission denied"
# define ERR_BIN_NOT_FOUND "command not found"
# define ERR_BIN_IS_FOLDER "Is a directory"
# define ERR_BIN_NON_EXECUTABEL "Permission denied"
# define ERR_BIN_NO_SUCH_FOLDER "No such file or directory"
# define ERR_BLTN_EXPORT_NO_OPTIONS "export: Minshell allows no options"

/*** Colors ***/
# define BOLD	"\033[1m"
# define BLUE	"\033[1;36m"
# define RED     "\033[1;31m"
# define PURPLE  "\033[1;35m"
# define NS	"\033[0m"

/*** Functions ***/
void	debug_print_cmds(t_cmd_list *cmd, int active);

#endif
