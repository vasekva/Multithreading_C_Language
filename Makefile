NAME	= philo

INCLUDES	=	-I ./includes/
SRCS_DIR	=	./srcs/
OBJS_DIR	=	./objs/

SRCS_FILES	= main.c exception.c check_functions.c
OBJS_FILES	= $(SRCS_FILES:.c=.o)

SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_FILES))

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

all:
				mkdir -p $(OBJS_DIR)
				@($(CC)  $(CFLAGS) $(INCLUDES) $(SRCS) -o $(NAME))
				#mv $(OBJS_FILES) $(OBJS_DIR)

clean:
				rm -rf $(OBJS_DIR)*

fclean:			clean
				rm -rf $(OBJS_DIR)
				rm -rf $(NAME)

re:				fclean, all

.PHONY: all, clean, fclean, re