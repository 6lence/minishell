# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 10:13:49 by ashalagi          #+#    #+#              #
#    Updated: 2023/11/08 13:46:27 by ashalagi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_strstr.c \
	ft_strcpy.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_strrchr.c \
	ft_realloc.c \
	ft_memalloc.c \
	ft_strcmp.c \
	ft_tablen.c \
	get_next_line_bonus.c \
	get_next_line_utils_bonus.c 

CC = gcc

AR = ar rcs

CFLAGS = -Wall -Wextra -Werror

OBJ = ${SRC:.c=.o}

BONUS_OBJ = ${BONUS_SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	@${AR} ${NAME} ${OBJ}

clean:
	@rm -rf ${OBJ} ${BONUS_OBJ}

fclean: clean
	@rm -rf ${NAME}

re: fclean all
