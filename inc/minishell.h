/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:27:56 by paribeir          #+#    #+#             */
/*   Updated: 2024/08/18 09:58:20 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <dirent.h>
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

/*** Structs ***/

typedef struct s_cmd
{
	int		pipe[2];
	int		saved_stdout;
	int		saved_stdin;
	char	**envp;
	int		pipe_status;
	int		fdout_status;
	int		exit_status;
}	t_cmd;

/*** Error Messages ***/

# define ERR_BIN_NOT_FOUND "minishell: No such file or directory\n"
# define ERR_ECHO_FLAGS "Only flag '-n' may be used with echo command\n"

/*** Colors ***/

# define BLUE	"\033[1;36m"
# define NS	"\033[0m"

#endif
