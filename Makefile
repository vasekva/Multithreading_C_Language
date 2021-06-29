NAME			= philo

INCLUDES		=	-I ./includes/
LIBFT_DIR		=	./libft/
LIBRARY_PATH	=	./libft/libft.a
SRCS_DIR		=	./srcs/
OBJS_DIR		=	./objs/

SRCS_FILES		= main.c actions.c lifecycle_utils.c \
					exception.c check_functions.c

OBJS_FILES		= $(SRCS_FILES:.c=.o)

SRCS			= $(addprefix $(SRCS_DIR), $(SRCS_FILES))

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror

all:
				$(MAKE) -C $(LIBFT_DIR)
				mkdir -p $(OBJS_DIR)
				@($(CC) $(CFLAGS) $(INCLUDES) $(LIBRARY_PATH) $(SRCS) -o $(NAME))

clean:
				rm -rf $(OBJS_DIR)*
				$(MAKE) fclean -C $(LIBFT_DIR)

fclean:			clean
				rm -rf $(OBJS_DIR)
				rm -rf $(NAME)

re:				fclean, all

.PHONY: all, clean, fclean, re