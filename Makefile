# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdach <jdach@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/19 15:45:03 by paribeir          #+#    #+#              #
#    Updated: 2024/08/17 00:09:20 by jdach            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -lreadline
CC = cc
OPTIONS = -c -g

ifeq ($(shell uname -s), Darwin)
  LDFLAGS += -L/opt/homebrew/opt/readline/lib
  CPPFLAGS += -I/opt/homebrew/opt/readline/include
endif

#NAMES
NAME = minishell
NAME_BONUS = minishell_bonus

#DIRECTORIES
OBJ_DIR = obj/
LIB_DIR = lib/
SRC_DIR = src/

#SOURCEFILES
SRC_MINISHELL = \
exe/exe_bin.c \
exe/exe_bin_args.c \
exe/exe_bin_get_bin_path.c \
exe/exe_bltns.c \
exe/exe_bltns_cd.c \
exe/exe_bltns_echo.c \
exe/exe_bltns_env.c \
exe/exe_bltns_exit.c \
exe/exe_bltns_export.c \
exe/exe_bltns_pwd.c \
exe/exe_bltns_unset.c \
exe/exe_cleanup.c \
exe/exe_cleanup_strarray.c \
exe/exe_err.c \
exe/exe_directs.c \
exe/exe_directs_append.c \
exe/exe_directs_here_doc.c \
exe/exe_directs_redir_in.c \
exe/exe_directs_redir_out.c \
exe/exe_env_get_var.c \
exe/exe_env_get_var_address.c \
exe/exe_env_cpy.c \
exe/exe_env_set_var.c \
exe/exe_pipe_in.c \
exe/exe_pipe_out.c \
exe/exe_signals.c \
exe/exe.c \
main.c \
parsing/env_variables.c \
parsing/expansions.c \
parsing/heredoc.c \
parsing/hex_to_str.c \
parsing/parser.c \
parsing/quotes.c \
parsing/tokenizer_utils.c \
parsing/tokenizer.c \
parsing/wildcard.c

SRCS_MINISHELL = $(addprefix $(SRC_DIR), $(SRC_MINISHELL))

SRC_MINISHELL_BONUS =
SRCS_MINISHELL_BONUS = $(addprefix $(SRC_DIR), $(SRC_MINISHELL_BONUS))

#OBJECTFILES
OBJ_MINISHELL = $(SRC_MINISHELL:.c=.o)
OBJS_MINISHELL = $(addprefix $(OBJ_DIR), $(OBJ_MINISHELL))

OBJ_MINISHELL_BONUS = $(SRC_MINISHELL_BONUS:.c=.o)
OBJS_MINISHELL_BONUS = $(addprefix $(OBJ_DIR), $(OBJ_MINISHELL_BONUS))

#HEADERFILES
INCS = -I inc/

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS_MINISHELL)
	make -C $(LIB_DIR)libft
	$(CC) $(OBJS_MINISHELL) $(LDFLAGS) $(FLAGS) $(LIB_DIR)libft/libft.a -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	mkdir -p $(dir $@)
	$(CC) $(INCS) $(CPPFLAGS) $(OPTIONS) $< -o $@

clean:
	make clean -C $(LIB_DIR)libft
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIB_DIR)libft
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re
