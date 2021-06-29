cmake_minimum_required(VERSION 3.19)
project(My_PHILO C)

set(CMAKE_C_STANDARD 11)

include_directories(includes)

add_executable(My_PHILO
        includes/errors.h
        includes/main_header.h
        srcs/lifecycle_utils.c
        srcs/actions.c
        srcs/main.c
        libft/srcs/ft_atoi.c
        libft/srcs/ft_strlen.c
        libft/srcs/ft_calloc.c
        libft/srcs/ft_itoa.c
        libft/srcs/ft_memset.c
        libft/srcs/ft_strncmp.c
        )
