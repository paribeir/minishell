FLAGS = -Wall -Wextra -Werror
OPTIONS = -c

#DIRECTORIES
OBJS_DIR = objs/

#NAMES
NAME = libft.a
MAIN_NAME = a.out

#SOURCEFILES
LIBRARY_SOURCEFILES = \
ft_atoi.c \
ft_calloc.c \
ft_bzero.c \
ft_get_next_line.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_itoa.c \
ft_lstadd_back.c \
ft_lstadd_front.c \
ft_lstclear.c \
ft_lstdelone.c \
ft_lstiter.c \
ft_lstlast.c \
ft_lstnew.c \
ft_lstmap.c \
ft_lstsize.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_printf_c.c \
ft_printf_filter_dot.c \
ft_printf_filter_plus.c \
ft_printf_filter_space.c \
ft_printf_filter_width.c \
ft_printf_filter_x.c \
ft_printf_filter.c \
ft_printf_getflags.c \
ft_printf_id.c \
ft_printf_p.c \
ft_printf_percent.c \
ft_printf_s.c \
ft_printf_u.c \
ft_printf_x.c \
ft_printf.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putstr_fd.c \
ft_split.c \
ft_strchr.c \
ft_strdup.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlcpy.c \
ft_strlcat.c \
ft_strlen.c \
ft_strmapi.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strtrim.c \
ft_strtolower.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c
MAIN_SOURCEFILES = main.c

#OBJECTFILES
LIBRARY_OBJECTFILES = $(addprefix $(OBJS_DIR), $(LIBRARY_SOURCEFILES:.c=.o))
MAIN_OBJECTFILES = $(addprefix $(OBJS_DIR), $(MAIN_SOURCEFILES:.c=.o))

all: $(NAME)

$(NAME): $(LIBRARY_OBJECTFILES)
	ar rc $(NAME) $(LIBRARY_OBJECTFILES)

test: $(MAIN_OBJECTFILES)
	cc $(FLAGS) $(MAIN_OBJECTFILES) -o $(MAIN_NAME) $(NAME)

$(OBJS_DIR)%.o : %.c
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) -g $(OPTIONS) $< -o $@

clean:
	rm -rf $(OBJS_DIR)
	rm -f *.gch

fclean: clean
	rm -f $(NAME)
	rm -f $(MAIN_NAME)

re: fclean all

run: fclean all bonus test
	#===== OUTPUT ====#
	./$(MAIN_NAME) | cat -e

valgrind: fclean bonus test
	#===== OUTPUT ====#
	valgrind --leak-check=yes ./$(MAIN_NAME) | cat -e

leaks: fclean bonus test
	#===== OUTPUT ====#
	leaks --atExit -- ./$(MAIN_NAME) | cat -e

.PHONY: all clean fclean re bonus
