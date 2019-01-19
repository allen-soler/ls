# Name of the library
NAME = libft.a

# Commands
MKDIR_P = mkdir -p

# Define all the compiling flags
CFLAGS += -Wall -Werror -Wextra
CC := gcc

# Define all library flags
LFLAGS += -I.
AR = ar rcs
RLIB := ranlib

# Name of the directories
OBJ_DIR := objs/

# Files
HEAD = libft.h
#				LIBC FUNCTIONS
SRCS += ft_memset.c		\
		ft_bzero.c		\
		ft_memcpy.c		\
		ft_memccpy.c	\
		ft_memmove.c	\
		ft_memchr.c		\
		ft_memcmp.c		\
		ft_strlen.c		\
		ft_strdup.c		\
		ft_strcpy.c		\
		ft_strncpy.c	\
		ft_strcat.c		\
		ft_strncat.c	\
		ft_strlcat.c	\
		ft_strchr.c		\
		ft_strrchr.c	\
		ft_strstr.c		\
		ft_strnstr.c	\
		ft_strcmp.c		\
		ft_strncmp.c	\
		ft_atoi.c		\
		ft_isalpha.c	\
		ft_isdigit.c	\
		ft_isalnum.c	\
		ft_isascii.c	\
		ft_isprint.c	\
		ft_toupper.c	\
		ft_tolower.c	\
		ft_isspace.c

#					ADDITIONAL FUNCTIONS
SRCS += ft_memalloc.c	\
		ft_memdel.c		\
		ft_strnew.c		\
		ft_strdel.c		\
		ft_striter.c	\
		ft_striteri.c	\
		ft_strmap.c		\
		ft_strmapi.c	\
		ft_strequ.c		\
		ft_strnequ.c	\
		ft_strsub.c		\
		ft_strjoin.c	\
		ft_strtrim.c	\
		ft_strsplit.c	\
		ft_itoa.c		\
		ft_strclr.c		\
		ft_putchar.c	\
		ft_putchar_fd.c	\
		ft_putstr.c		\
		ft_putstr_fd.c	\
		ft_putnbr.c		\
		ft_putnbr_fd.c	\
		ft_putendl.c	\
		ft_putendl_fd.c \
		ft_strndup.c		
#					CHAINED LIST FUNCTIONS
SRCS += ft_lstnew.c		\
		ft_lstdelone.c	\
		ft_lstdel.c		\
		ft_lstadd.c		\
		ft_lstiter.c	\
		ft_lstmap.c

OBJS := $(SRCS:%.c=%.o)

# Path to the directories
# SRCS := $(wildcard $(*.c)
# OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compile and create everything.
all: $(NAME)

# This won't run if the .o files don't exist or are not modified
$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@$(RLIB) $(NAME)

# This won't run if the source files don't exit or are not modified
$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) -c $(SRCS)

# Removes all the object files and directory
clean:
	@rm -f $(OBJS)

# Removes everything that has been created by the makefile
fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
