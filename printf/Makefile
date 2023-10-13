HEADER = ./

SRC = ./src/

FILES_C = ${SRC}ft_printf.c \
		  ${SRC}ft_put.c \
		  ${SRC}ft_hexa.c \
		  ${SRC}ft_verifs.c \
		  ${SRC}ft_flags.c \
		  ${SRC}ft_flags2.c \
		  ${SRC}ft_flags3.c \
		  ${SRC}ft_flags4.c \
		  ${SRC}ft_flags5.c \
		  ${SRC}ft_flags6.c \
		  ${SRC}ft_flags_fonct.c \

LIBFT_PATH = ${SRC}libft/

LIBFT = ${SRC}libft/libft.a

FILES_O = ${FILES_C:.c=.o}

FILES_H = ${HEADER}ft_printf.h

FLAGS = -Wall -Wextra -Werror -g

NAME = libftprintf.a

all: ${NAME}

${LIBFT}:
	make -C ${LIBFT_PATH} all bonus

.c.o:
	gcc ${FLAGS} -I ${HEADER} -c $< -o ${<:.c=.o}

bonus: all

${NAME}: ${LIBFT} ${FILES_O}
	cp ${LIBFT} .
	mv libft.a ${NAME}
	ar -rc ${NAME} ${FILES_O}

clean:
	rm -f ${FILES_O}
	make -C ${LIBFT_PATH} fclean

fclean: clean
	rm -f ${NAME}

re: fclean all

