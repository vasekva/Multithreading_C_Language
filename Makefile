NAME			= philo
BONUS_NAME		= philo_bonus

INCLUDES		=	-I ./includes/
MAIN_SRCS_DIR	=	./main_part/srcs/
TMP_SRCS_DIR	=	./new_main_part/srcs/
BONUS_SRCS_DIR	=	./bonus_part/srcs/
OBJS_DIR		=	./objs/

MAIN_FILES		= main.c cycle_functions.c check_functions.c itoa_exception.c lib_functions.c lifecycle_utils.c

BONUS_FILES		= main.c actions.c check_functions.c itoa_exception.c lib_functions.c lifecycle_utils.c

OBJS_FILES		= $(SRCS_FILES:.c=.o)

MAIN_SRCS		= $(addprefix $(MAIN_SRCS_DIR), $(MAIN_FILES))
BONUS_SRCS		= $(addprefix $(BONUS_SRCS_DIR), $(BONUS_FILES))

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror

all:
				@echo	"\033[1m\033[32m===	MAIN_PART COMPILATION...	===\033[0m"
				mkdir -p $(OBJS_DIR)
				@($(CC) $(CFLAGS) $(INCLUDES) $(MAIN_SRCS) -o $(NAME))

bonus:
				@echo	"\033[1m\033[31m===	BONUS_PART COMPILATION...	===\033[0m"
				mkdir -p $(OBJS_DIR)
				@($(CC) $(CFLAGS) $(INCLUDES) $(BONUS_SRCS) -o $(BONUS_NAME))

clean:
				rm -rf $(OBJS_DIR)

fclean:			clean
				rm -rf $(NAME)
				rm -rf $(BONUS_NAME)

re:				fclean, all

.PHONY: all, clean, fclean, re