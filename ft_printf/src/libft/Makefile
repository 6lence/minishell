HEADER = ./
SOURCE = ./
FILES_C = ${SOURCE}ft_isalpha.c \
	${SOURCE}ft_isdigit.c \
	${SOURCE}ft_isalnum.c \
	${SOURCE}ft_isascii.c \
	${SOURCE}ft_isprint.c \
	${SOURCE}ft_strlen.c \
	${SOURCE}ft_memset.c \
	${SOURCE}ft_bzero.c \
	${SOURCE}ft_memcpy.c \
	${SOURCE}ft_memmove.c \
	${SOURCE}ft_strlcpy.c \
	${SOURCE}ft_strlcat.c \
	${SOURCE}ft_toupper.c \
	${SOURCE}ft_tolower.c \
	${SOURCE}ft_strchr.c \
	${SOURCE}ft_strrchr.c \
	${SOURCE}ft_strncmp.c \
	${SOURCE}ft_strcmp.c \
	${SOURCE}ft_memchr.c \
	${SOURCE}ft_memcmp.c \
	${SOURCE}ft_strnstr.c \
	${SOURCE}ft_atoi.c \
	${SOURCE}ft_calloc.c \
	${SOURCE}ft_strdup.c \
	${SOURCE}ft_substr.c \
	${SOURCE}ft_strjoin.c\
	${SOURCE}ft_strtrim.c \
	${SOURCE}ft_split.c \
	${SOURCE}ft_itoa.c \
	${SOURCE}ft_strmapi.c \
	${SOURCE}ft_striteri.c \
	${SOURCE}ft_putchar_fd.c \
	${SOURCE}ft_putstr_fd.c \
	${SOURCE}ft_putendl_fd.c \
	${SOURCE}ft_putnbr_fd.c \
	${SOURCE}get_next_line_bonus.c \
	${SOURCE}ft_strsrch.c \

FILES_C_BONUS = ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		
FILES_O = ${FILES_C:.c=.o}

FILES_O_BONUS = ${FILES_C_BONUS:.c=.o}

FILES_H = ${HEADER}libft.h

FLAGS = -Wall -Wextra -Werror -g

NAME = libft.a

all: ${NAME}

bonus: ${FILES_O_BONUS}
	ar -rc ${NAME} ${FILES_O_BONUS}

.c.o:
	gcc ${FLAGS} -I ${HEADER} -c $< -o ${<:.c=.o}

${NAME}: ${FILES_O}
	ar -rc ${NAME} ${FILES_O}

clean:
	rm -f ${FILES_O} ${FILES_O_BONUS}

fclean: clean
	rm -f ${NAME}

re: fclean all
