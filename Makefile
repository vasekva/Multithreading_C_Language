NAME			= philo
BONUS_NAME		= philo_bonus

INCLUDES		=	-I ./includes/
MAIN_SRCS_DIR	=	./main_part/srcs/
TMP_SRCS_DIR	=	./new_main_part/srcs/
BONUS_SRCS_DIR	=	./bonus_part/srcs/
OBJS_DIR		=	./objs/

SRCS_FILES		= main.c actions.c lifecycle_utils.c lifecycle_utils_1.c \
					lifecycle_utils_2.c check_functions.c

TMP_SRCS_FILES		= main.c actions.c check_functions.c lifecycle_utils.c \
						lifecycle_utils_1.c lifecycle_utils_2.c

OBJS_FILES		= $(SRCS_FILES:.c=.o)

MAIN_SRCS			= $(addprefix $(MAIN_SRCS_DIR), $(SRCS_FILES))
TMP_SRCS		= $(addprefix $(TMP_SRCS_DIR), $(TMP_SRCS_FILES))
BONUS_SRCS			= $(addprefix $(BONUS_SRCS_DIR), $(SRCS_FILES))

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

tmp:
				@echo	"\033[1m\033[32m===	NEW MAIN_PART COMPILATION...	===\033[0m"
				mkdir -p $(OBJS_DIR)
				@($(CC) $(CFLAGS) $(INCLUDES) $(TMP_SRCS) -o $(NAME))
clean:
				rm -rf $(OBJS_DIR)

fclean:			clean
				rm -rf $(NAME)
				rm -rf $(BONUS_NAME)

re:				fclean, all

.PHONY: all, clean, fclean, re