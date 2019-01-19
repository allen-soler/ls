
CC = gcc

FLAGS = -Wall -Werror -Wextra

NAME = ls

DIR_S = src

LIBFT = libftprintf

DIR_O = temporary

DIR_H = includes

SOURCES = ft_stats.c getpath.c list_tools.c ls_l.c main.c misc.c sort_list.c

SRCS = $(addprefix $(DIR_S)/, $(SOURCES))

OBJS = $(addprefix $(DIR_O)/, $(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT)/libftprintf.a -I $(DIR_H)

$(DIR_O)/%.o: $(DIR_S)/%.c
	@mkdir -p temporary
	$(CC) $(FLAGS) -I $(DIR_H) -o $@ -c $<

clean:
	rm -f $(OBJS)
	rm -rf $(DIR_O)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re: fclean all
