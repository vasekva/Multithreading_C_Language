NAME = libft.a

INCLUDES	=	-I ./includes
SRCS_DIR	=	./srcs/
OBJS_DIR	=	./objs/

FUNCTIONS	=	ft_strlen.c ft_atoi.c ft_itoa.c ft_strncmp.c \
				ft_calloc.c ft_memset.c

SRCS		=	$(addprefix $(SRCS_DIR),	$(FUNCTIONS))
OBJS		=	$(addprefix $(OBJS_DIR),	$(FUNCTIONS:.c=.o))

CC = gcc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -c

all:	$(NAME)

$(NAME):
				mkdir -p $(OBJS_DIR)
				$(CC)  $(INCLUDES) $(CFLAGS) $(SRCS)
				mv $(FUNCTIONS:.c=.o) $(OBJS_DIR)
				ar -rc $(NAME) $(OBJS)
				ranlib $(NAME)

clean:
	$(RM) $(OBJS_DIR)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all, clean, fclean, re, bonus