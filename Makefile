# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdach <jdach@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/19 15:45:03 by paribeir          #+#    #+#              #
#    Updated: 2024/07/17 08:45:59 by jdach            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -lreadline
CC = cc
OPTIONS = -c -g

#NAMES
NAME = minishell
NAME_BONUS = minishell_bonus

#DIRECTORIES
OBJ_DIR = obj/
LIB_DIR = lib/
SRC_DIR = src/

#SOURCEFILES
SRC_MINISHELL = \
exe/exe_append.c \
exe/exe_bin.c \
exe/exe_bltn_echo.c \
exe/exe_cleanup.c \
exe/exe_err.c \
exe/exe_get_bin_path.c \
exe/exe_get_in_out.c \
exe/exe_here_doc_fd.c \
exe/exe_look_ahead.c \
exe/exe_redir_in.c \
exe/exe_redir_out.c \
exe/exe_run.c \
main.c \
parsing/env_variables.c \
parsing/expansions.c \
parsing/heredoc.c \
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
	$(CC) $(OBJS_MINISHELL) $(FLAGS) $(LIB_DIR)libft/libft.a -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	mkdir -p $(dir $@)
	$(CC) $(INCS) $(OPTIONS) $< -o $@

clean:
	make clean -C $(LIB_DIR)libft
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIB_DIR)libft
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re
