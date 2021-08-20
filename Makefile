NAME			= philo
BONUS_NAME		= philo_bonus

INCLUDES		=	-I ./includes/
LIBFT_DIR		=	./libft/
LIBRARY_PATH	=	./libft/libft.a
MAIN_SRCS_DIR	=	./main_part/srcs/
BONUS_SRCS_DIR	=	./bonus_part/srcs/
OBJS_DIR		=	./objs/

SRCS_FILES		= main.c actions.c lifecycle_utils.c \
					exception.c check_functions.c

BONUS_SRCS_FILES	= main.c utils_bonus.c actions.c \
                      	check_functions.c exception.c

OBJS_FILES		= $(SRCS_FILES:.c=.o)

MAIN_SRCS			= $(addprefix $(MAIN_SRCS_DIR), $(SRCS_FILES))
BONUS_SRCS			= $(addprefix $(BONUS_SRCS_DIR), $(BONUS_SRCS_FILES))

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror

all:
				@echo	"\033[1m\033[32m===	MAIN_PART COMPILATION...	===\033[0m"
				$(MAKE) -C $(LIBFT_DIR)
				mkdir -p $(OBJS_DIR)
				@($(CC) $(CFLAGS) $(INCLUDES) $(LIBRARY_PATH) $(MAIN_SRCS) -o $(NAME))

bonus:
				@echo	"\033[1m\033[31m===	BONUS_PART COMPILATION...	===\033[0m"
				$(MAKE) -C $(LIBFT_DIR)
				mkdir -p $(OBJS_DIR)
				@($(CC) $(CFLAGS) $(INCLUDES) $(LIBRARY_PATH) $(BONUS_SRCS) -o $(BONUS_NAME))
clean:
				rm -rf $(OBJS_DIR)*
				$(MAKE) fclean -C $(LIBFT_DIR)

fclean:			clean
				rm -rf $(OBJS_DIR)
				rm -rf $(NAME)

re:				fclean, all

.PHONY: all, clean, fclean, re