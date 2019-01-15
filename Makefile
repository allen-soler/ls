# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jallen <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 13:52:04 by jallen            #+#    #+#              #
#    Updated: 2019/01/15 14:17:04 by jallen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = ft_ls

LIBFT = src/libft

PRINTF = src/ft_printf

SRC =  get_path.c	\
	   list_tools.c \
	   ft_stats.c	\
	   ls_ls.c		\
	   main.c		\
	   sort_list.c	\

SRCS = $(addprefix src/, $(SRC))

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C src/libft
	@make -C src/ft_printf
	$(CC) -o $(NAME) $(FLAGS) $(OBJ) $(LIBFT) $(PRINTF)
	#@make fclean -C libft

$(OBJ): src//%.c
	@mkdir -p temporary
	@$(CC) $(FLAGS) -I $(DIR_H) -o $@ -c $<

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

test:
	make re
	gcc -g -o printf src/*.c libftprintf.a libft.a -I includes/ft_ls.h

.PHONY: clean fclean all re
