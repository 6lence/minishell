# Define your source files and target executable
SRC_DIR := ./src
SRC_FILES :=	minishell.c \
				ft_parsing.c \
				ft_parsing_2.c \
				ft_errors.c \
				ft_lstutils.c \
				ft_execute_pipe.c \
				ft_utils.c \
				ft_free.c \

OBJ_DIR := ./obj
EXECUTABLE := minishell

# Generate a list of object files with paths
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))

# Compiler and compiler flags
CC := gcc
CFLAGS := -Wall -Werror -Wextra -g

# Additional dependencies
LFT := ./ft_printf/libftprintf.a
LIB := -L./ft_printf -lftprintf

RM := rm -f

all: $(OBJ_DIR) $(LFT) $(EXECUTABLE)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LFT):
	@make -s -C ./ft_printf/ all

$(EXECUTABLE): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $^ $(LIB) -lreadline -o $@  # Moved -lreadline here
	@echo "\033[32m✅ Done !\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@make -s -C ./ft_printf/ clean

fclean: clean
	@$(RM) $(EXECUTABLE)
	@make -s -C ./ft_printf/ fclean

re: fclean all

.PHONY: all clean fclean re
