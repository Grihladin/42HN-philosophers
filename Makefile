NAME	:= philosophers

#################################
#			Config				#
#################################

CC = gcc

#################################
#			Flags				#
#################################

DEBUG_FLAGS	:= -g -fsanitize=address -fsanitize=undefined -O0
CFLAGS		:= -Wall -Wextra -Werror -fcolor-diagnostics

#################################
#			Files				#
#################################

SRC_DIR = philo
VPATH = $(SRC_DIR)

SRC = \
$(SRC_DIR)/main.c \
$(SRC_DIR)/utils.c

OBJ_DIR = objects
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = librarys/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a



#################################
#			Rules				#
#################################

all: $(NAME)
	@echo "\033[0;32m$(NAME) built successfully!\033[0m"

$(NAME): $(OBJ) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_LIB)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
