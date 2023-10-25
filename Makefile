# Define your source files and target executable
SRC_DIR := ./src
SRC_FILES :=	minishell.c \
				ft_parsing_1.c \
				ft_parsing_2.c \
				ft_parsing_3.c \
				ft_parsing_4.c \
				ft_parsing_5.c \
				ft_parsing_6.c \
				ft_errors.c \
				ft_lstutils.c \
				ft_listutils_2.c \
				ft_execute_pipe.c \
				ft_utils.c \
				ft_free.c \
				builtin.c \
				ft_cd.c \
				ft_echo.c \
				ft_env.c \
				ft_exit.c \
				ft_export.c \
				ft_pwd.c \
				ft_unset.c \
				execute_priorities.c

OBJ_DIR := ./obj
EXECUTABLE := minishell

# Generate a list of object files with paths
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))

# Compiler and compiler flags
CC := gcc
CFLAGS := -Wall -Werror -Wextra -g

# Additional dependencies
#LFT := ./ft_printf/libftprintf.a
#LIB := -L./ft_printf -lftprintf
LFT := ./libft/libft.a
LIB := -L./libft -lft

RM := rm -f

all: $(OBJ_DIR) $(LFT) $(EXECUTABLE)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LFT):
#	@make -s -C ./ft_printf/ all
	@make -s -C ./libft/ all

$(EXECUTABLE): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $^ $(LIB) -lreadline -o $@ 
	@echo "\033[32m✅ Done! Executable $(EXECUTABLE) is ready.\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
#	@make -s -C ./ft_printf/ clean
	@make -s -C ./libft/ clean
	@echo "\033[32m✅ Done! Object files removed.\033[0m"

fclean: clean
	@$(RM) $(EXECUTABLE)
#	@make -s -C ./ft_printf/ fclean
	@make -s -C ./libft/ fclean
	@echo "\033[32m✅ Done! Executable $(EXECUTABLE) removed.\033[0m"

re: fclean all

.PHONY: all clean fclean re
